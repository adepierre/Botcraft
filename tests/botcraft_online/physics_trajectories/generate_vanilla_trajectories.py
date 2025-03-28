import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import os
import platform
from queue import Queue
import re
import shutil
import subprocess
import time
import threading
from typing import Optional
import urllib.request
import zipfile

MANIFEST_URL = "https://launchermeta.mojang.com/mc/game/version_manifest.json"
JAVA_RUNTIME_ALL_URL = "https://launchermeta.mojang.com/v1/products/java-runtime/2ec0cc96c44e5a76b9c8b7c39df7210883d12871/all.json"
OBJECTS_URL = "https://resources.download.minecraft.net"
ASM_URL = "https://repository.ow2.org/nexus/content/repositories/releases/org/ow2/asm"
ASM_VERSION = "9.7.1"
MCP_URL = "https://raw.githubusercontent.com/MinecraftForge/MCPConfig/master/versions/release"
PLAYER_NAME = "PhysicsBuddy"
VERBOSE_SERVER = False
INPUTS_KEYS = ["forward", "left", "backward", "right", "jump", "sneak", "sprint", "yRot", "xRot"]

def download_file(url: str, destination_folder: str, validate_size: bool = False) -> str:
    os.makedirs(destination_folder, exist_ok=True)
    destination = os.path.join(destination_folder, url.split("/")[-1])
    if os.path.exists(destination):
        if validate_size:
            request_size = urllib.request.urlopen(urllib.request.Request(url, method="HEAD"))
            content_length = request_size.headers.get("Content-Length")
            if not content_length is None and int(content_length) == os.path.getsize(destination):
                return destination
        else:
            return destination
    with urllib.request.urlopen(url) as response:
        data = response.read()

    with open(destination, "wb") as f:
        f.write(data)

    return destination

class Server:
    def __init__(self, base_folder: str, manifest: dict, dat_path: str, structures_folder: str, java_exe: str):
        print("Setup server...")
        print("\tCopy files...")
        version = manifest["id"]
        # Copy structure files
        structure_folder_dst = os.path.join(base_folder, "world", "generated", "minecraft", "structures") if version > "1.12.2" else os.path.join(base_folder, "world", "structures")
        os.makedirs(structure_folder_dst, exist_ok=True)
        if structures_folder:
            for f in os.listdir(structures_folder):
                shutil.copy(os.path.join(structures_folder, f), os.path.join(structure_folder_dst, f))

        # Copy custom level.dat file
        if dat_path != "" and os.path.isfile(dat_path):
            shutil.copy(dat_path, os.path.join(base_folder, "world", "level.dat"))

        # Accept EULA I guess
        with open(os.path.join(base_folder, "eula.txt"), "w") as f:
            f.write("eula=true")

        # Set server properties
        with open(os.path.join(base_folder, "server.properties"), "w") as f:
            if version < "1.14":
                f.write("difficulty=3\n")
                f.write("gamemode=1\n")
            else:
                f.write("difficulty=hard\n")
                f.write("gamemode=creative\n")
            f.write("enable-command-block=true\n")
            if version > "1.18.2":
                f.write("enforce-secure-profile=false\n")
            f.write("force-gamemode=true\n")
            f.write("generate-structures=false\n")
            f.write("level-seed=botcraft\n")
            f.write("level-type=flat\n")
            f.write("motd=Botcraft test server\n")
            f.write("network-compression-threshold=256\n")
            f.write("online-mode=false\n")
            f.write("spawn-monsters=false\n")
            f.write("spawn-protection=0\n")
            f.write("view-distance=5\n")
        print("\tDownload jar...")
        server_file = download_file(manifest["downloads"]["server"]["url"], base_folder, True)
        cmd = [
            java_exe,
            "-Xmx1024M",
            "-Xms1024M",
            "-jar",
            os.path.relpath(server_file, base_folder),
            "nogui"
        ]
        # Launch server
        print("\tStart server...")
        self.process = subprocess.Popen(cmd, cwd=base_folder, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)

        self.queue = Queue()
        self.queue_thread = threading.Thread(
            target=self._enqueue_output,
            daemon=True
        )
        self.queue_thread.start()

        # Let it unpack all libraries and create the world
        self.wait_regex(".*: Done \\([\\d.,]+s\\)! For help, type \"help\".*", 300)

        # Set all custom gamerules
        print("\tSet gamerules...")
        self._set_gamerule("announceAdvancements", "false")
        if version > "1.14.2":
            self._set_gamerule("disableRaids", "true")
        self._set_gamerule("doDaylightCycle", "false")
        self._set_gamerule("doFireTick", "false")
        if version > "1.14.4":
            self._set_gamerule("doInsomnia", "false")
        self._set_gamerule("doMobSpawning", "false")
        if version > "1.15.1":
            self._set_gamerule("doPatrolSpawning", "false")
            self._set_gamerule("doTraderSpawning", "false")
        self._set_gamerule("doWeatherCycle", "false")
        if version > "1.18.2":
            self._set_gamerule("doWardenSpawning", "false")
        self._set_gamerule("mobGriefing", "false")
        self._set_gamerule("randomTickSpeed", "0")
        self._set_gamerule("spawnRadius", "0")
        self._set_gamerule("spectatorsGenerateChunks", "true")

        print("Server ready!")

    def close(self):
        self.process.terminate()
        self.queue_thread.join()

    def _enqueue_output(self):
        while True:
            line = self.process.stdout.readline()
            if not line:
                break
            if VERBOSE_SERVER:
                print(f"[SERVER] - {line.strip()}")
            self.queue.put(line)

    def _set_gamerule(self, gamerule: str, value: str) -> None:
        self.send_command(f"gamerule {gamerule} {value}")
        self.wait_regex(f".*: Game ?rule {gamerule} (?:is now set to:|has been updated to) {value}.*", 5)

    def send_command(self, command: str):
        if VERBOSE_SERVER:
            print(f"[PYTHON] - {command.strip()}")
        self.process.stdin.write(command + "\n")
        self.process.stdin.flush()

    def wait_regex(self, regex: str, timeout: Optional[float] = None) -> None:
        pattern = re.compile(regex)
        start_time = time.time()
        while True:
            if self.queue.qsize() != 0:
                line = self.queue.get(False)
                if pattern.search(line):
                    return
            elif not timeout is None and time.time() - start_time > timeout:
                raise TimeoutError(f"Timeout ({timeout}s) reached waiting for pattern {regex}")
            else:
                time.sleep(0.001)

def setup_client(base_folder: str, manifest: dict, patcher: str, java_exe: str) -> subprocess.Popen:
    print("Setup client...")
    print("\tDownload jar...")
    # Download Jar file
    client_jar = download_file(manifest["downloads"]["client"]["url"], base_folder, True)

    # Setup patcher and patch the client
    print("\tPatch client...")
    if manifest["id"] < "1.14.4":
        mapping_file = download_file(f"{MCP_URL}/{manifest['id']}/joined.tsrg", base_folder)
    else:
        mapping_file = download_file(manifest["downloads"]["client_mappings"]["url"], base_folder)
    folder = os.path.dirname(client_jar)
    filename = os.path.basename(client_jar)
    download_file(f"{ASM_URL}/asm/{ASM_VERSION}/asm-{ASM_VERSION}.jar", os.path.join(folder, "patcher_libs"))
    download_file(f"{ASM_URL}/asm-commons/{ASM_VERSION}/asm-commons-{ASM_VERSION}.jar", os.path.join(folder, "patcher_libs"))
    subprocess.run([
        java_exe,
        "-cp", "patcher_libs/*",
        os.path.relpath(patcher, folder),
        filename,
        "patched_" + filename,
        os.path.relpath(mapping_file, folder),
        manifest["id"],
    ], cwd=folder, check=True)
    patched_jar = os.path.join(folder, "patched_" + filename)

    # Download logging config
    log_file_path = download_file(manifest["logging"]["client"]["file"]["url"], base_folder)

    # Download libraries
    print("\tDownload libraries...")
    current_os = platform.system().lower().replace("darwin", "osx")
    def download_lib(lib):
        try:
            # If no rules, default to True, if rules, default to False
            required = not "rules" in lib or len(lib["rules"]) == 0
            for rule in lib.get("rules", []):
                # If we found a matching rule, the result is the new required
                if not "os" in rule or rule["os"]["name"] == current_os:
                    required = rule["action"] == "allow"
            if not required:
                return
            if "artifact" in lib["downloads"]:
                download_file(lib["downloads"]["artifact"]["url"], os.path.join(base_folder, "libraries", os.path.dirname(lib["downloads"]["artifact"]["path"])))
            if "natives" in lib and current_os in lib["natives"]:
                downloaded_native = download_file(lib["downloads"]["classifiers"][lib["natives"][current_os]]["url"], os.path.join(base_folder, "libraries", os.path.dirname(lib["downloads"]["classifiers"][lib["natives"][current_os]]["path"])))
                # TODO: filter using extract/exclude to not extract META-INF folders and sha1 files (doesn't really matter, just cleaner)
                with zipfile.ZipFile(downloaded_native) as zipped:
                    zipped.extractall(os.path.join(base_folder, "natives"))
        except Exception as e:
            print(f"Exception while processing library {lib['name']}: {repr(e)}")
    # If it didn't exist, create the natives folder
    os.makedirs(os.path.join(base_folder, "natives"), exist_ok=True)

    with ThreadPoolExecutor(max_workers=8) as executor:
        executor.map(lambda lib: download_lib(lib), manifest["libraries"])

    # Download asset objects
    print("\tDownload assets...")
    asset_index = download_file(manifest["assetIndex"]["url"], os.path.join(base_folder, "assets", "indexes"))
    with open(asset_index, "r") as f:
        objects = json.load(f)["objects"]
    def download_object(o):
        name, v = o
        try:
            download_file(f"{OBJECTS_URL}/{v['hash'][:2]}/{v['hash']}", os.path.join(base_folder, "assets", "objects", v["hash"][:2]))
        except Exception as e:
            print(f"Exception while processing object {name}: {repr(e)}")

    with ThreadPoolExecutor(max_workers=8) as executor:
        executor.map(lambda p: download_object(p), objects.items())

    # Recreate classpath with all libraries
    classpath = ""
    separator = ";" if current_os == "windows" else ":"
    for lib in manifest["libraries"]:
        if not "artifact" in lib["downloads"]:
            continue
        # Skipped by rules
        if not os.path.exists(os.path.join(base_folder, "libraries", lib["downloads"]["artifact"]["path"])):
            continue
        classpath += "libraries/" + lib["downloads"]["artifact"]["path"] + separator
    # Add main jar
    classpath += os.path.relpath(patched_jar, base_folder)

    # Create all game command line args
    game_args = []
    if "minecraftArguments" in manifest: # 1.12.2
        game_args = manifest["minecraftArguments"].split(" ")
    else: # 1.13+
        # Skip dict with rules
        game_args = [arg for arg in manifest["arguments"]["game"] if isinstance(arg, str)]

    game_args_vals = {
        "auth_player_name": PLAYER_NAME,
        "version_name": manifest["id"],
        "game_directory": ".",
        "assets_root": "assets",
        "assets_index_name": manifest["assetIndex"]["id"],
        "auth_uuid": "00000000-0000-0000-0000-000000000000",
        "auth_access_token": "0",
        "clientid": "0",
        "auth_xuid": "0",
        "user_type": "legacy",
        "version_type": "release",
    }

    replace_regex = re.compile(".*\\${(.*)}.*")
    for i, arg in enumerate(game_args):
        m = replace_regex.match(arg)
        if m:
            key = m.group(1)
            game_args[i] = game_args[i].replace("${" + key + "}", game_args_vals[key])

    if manifest["id"] >= "1.20":
        game_args += [
            "--quickPlayMultiplayer",
            "127.0.0.1:25565"
        ]
    else:
        game_args += [
            "--server",
            "127.0.0.1",
            "--port",
            "25565"
        ]

    # Create all jvm command line args
    jvm_args = []
    jvm_args.append(manifest["logging"]["client"]["argument"].replace("path", "logpath"))
    if "arguments" in manifest:
        for option in manifest["arguments"]["jvm"]:
            if isinstance(option, str):
                jvm_args.append(option)
            else:
                required = not "rules" in option or len(option["rules"]) == 0
                for rule in option.get("rules", []):
                    if not "os" in rule or ("name" in rule["os"] and rule["os"]["name"] == current_os):
                        required = rule["action"] == "allow"
                    elif "arch" in rule["os"] and rule["os"]["arch"] == platform.machine():
                        required = rule["action"] == "allow"
                if required:
                    if isinstance(option["value"], list):
                        jvm_args += option["value"]
                    else:
                        jvm_args.append(option["value"])
    else: # 1.12.2, need to hardcode them
        if platform.machine() == "x86":
            jvm_args.append("-Xss1M")
        if current_os == "windows":
            jvm_args.append("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump")
        if current_os == "osx":
            jvm_args.append("-XstartOnFirstThread")
        jvm_args.append("-Djava.library.path=${natives_directory}")
        jvm_args.append("-Djna.tmpdir=${natives_directory}")
        jvm_args.append("-Dorg.lwjgl.system.SharedLibraryExtractPath=${natives_directory}")
        jvm_args.append("-Dio.netty.native.workdir=${natives_directory}")
        jvm_args.append("-Dminecraft.launcher.brand=${launcher_name}")
        jvm_args.append("-Dminecraft.launcher.version=${launcher_version}")
        jvm_args.append("-cp")
        jvm_args.append("${classpath}")

    # Add a few extra parameters
    jvm_args.append("-Xmx1024M")
    jvm_args.append("-Xms1024M")

    jvm_args_vals = {
        "logpath": os.path.basename(log_file_path),
        "natives_directory": "natives",
        "launcher_name": "launcher",
        "launcher_version": "3.14159",
        "classpath": classpath,
    }
    replace_regex = re.compile(".*\\${(.*)}.*")
    for i, arg in enumerate(jvm_args):
        m = replace_regex.match(arg)
        if m:
            key = m.group(1)
            jvm_args[i] = jvm_args[i].replace("${" + key + "}", jvm_args_vals[key])

    # Create options file, we don't need the render, so potato graphics will be fine
    print("\tCreate options file...")
    with open(os.path.join(base_folder, "options.txt"), "w") as f:
        f.write("version:1343\n") # 1.12.2, will also work for newer versions
        f.write("ao:false\n")
        f.write("autoJump:false\n")
        f.write("bobView:false\n")
        f.write("entityShadows:false\n")
        f.write("graphicsMode:0\n")
        if manifest["id"] >= "1.16.4":
            f.write("joinedFirstServer:true\n")
        f.write("maxFps:10\n") # FPS don't impact tick, lower it as much as possible
        f.write("mipmapLevels:0\n")
        f.write("narrator:0\n")
        f.write("overrideHeight:90\n")
        f.write("overrideWidth:160\n")
        f.write("particles:2\n")
        f.write("renderClouds:false\n")
        f.write("toggleCrouch:false\n")
        f.write("toggleSprint:false\n")
        f.write("tutorialStep:none\n")

    # Using any other java sometimes causes crash for some reasons so play safe
    print("\tInstall Minecraft JRE...")
    all_jre = download_file(JAVA_RUNTIME_ALL_URL, os.path.join(base_folder, "../.."), True)
    with open(all_jre, "r") as f:
        all_jre = json.load(f)

    jre_os_key = None
    # MacOS
    if current_os == "osx":
        jre_os_key = "mac-os-arm64" if "arm" in platform.machine().lower() else "mac-os"
    # Linux
    elif current_os == "linux":
        jre_os_key = "linux" if "64" in platform.machine() else "linux-i386"
    # Windows
    elif current_os == "windows":
        jre_os_key = "windows-arm64" if "arm" in platform.machine().lower() else "windows-x64" if "64" in platform.machine() else "windows-x86"

    if jre_os_key is None:
        raise RuntimeError("Can't deduce JRE version")

    jre_version = manifest["javaVersion"]["component"]
    jre_manifest_path = download_file(all_jre[jre_os_key][jre_version][0]["manifest"]["url"], os.path.join(base_folder, "../../jre"))
    with open(jre_manifest_path, "r") as f:
        jre_manifest = json.load(f)
    os.remove(jre_manifest_path)
    def download_jre_file(p):
        k, v = p
        if v["type"] != "file":
            return
        try:
            f = download_file(v["downloads"]["raw"]["url"], os.path.join(base_folder, "../../jre", jre_version, "/".join(k.split("/")[:-1])))
            if v.get("executable", False):
                os.chmod(f, 0o755)
        except Exception as e:
            print(f"Exception while processing JRE file {k}: {repr(e)}")

    with ThreadPoolExecutor(max_workers=8) as executor:
        executor.map(lambda p: download_jre_file(p), jre_manifest["files"].items())

    # Launch client
    print("\tLaunch patched client...")
    client = subprocess.Popen(
        [os.path.abspath(os.path.join(base_folder, "../../jre", jre_version, "bin/java"))] + jvm_args + [manifest["mainClass"]] + game_args,
        cwd=base_folder,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.STDOUT,
        text=True
    )

    print("Client started!")
    return client

def collect_trajectories(server: Server, in_folder: str, out_folder: str, client_folder: str, version: str, result_queue: Queue) -> None:
    try:
        print("Wait for the client to connect to the server...")
        server.wait_regex(f".*? {PLAYER_NAME} joined the game.*", 120)
        print("Collecting trajectories...")
        os.makedirs(out_folder, exist_ok=True)
        for file in os.listdir(in_folder):
            print(f"\t{file}")
            path = os.path.join(in_folder, file)
            with open(path, "r") as f:
                lines = f.readlines()
            test_min_version = lines[0].strip()
            if test_min_version and version < test_min_version:
                continue
            test_max_version = lines[1].strip()
            if test_max_version and version > test_max_version:
                continue
            outpath = os.path.join(out_folder, file.replace(".rawtraj", ".traj"))
            with open(outpath, "w") as f:
                f.write(test_min_version + "\n")
                f.write(test_max_version + "\n")
            structure_block_name = file[:-len(".rawtraj")].split("#")[0]
            line_index = 2
            while line_index < len(lines):
                section_name        = lines[line_index + 0].strip()
                section_min_version = lines[line_index + 1].strip()
                section_max_version = lines[line_index + 2].strip()
                gamemode            = lines[line_index + 3].strip()
                tp_offsets          = lines[line_index + 4].strip().split(";")
                commands_pre_run    = lines[line_index + 5].strip().split(";")
                commands_post_run   = lines[line_index + 6].strip().split(";")
                csv_key_header      = lines[line_index + 7].strip().split(";")
                assert len(csv_key_header) == len(INPUTS_KEYS)
                for k in INPUTS_KEYS:
                    assert k in csv_key_header
                keep_section = (not section_min_version or version >= section_min_version) and (not section_max_version or version <= section_max_version)
                line_index += 8
                trajectory_lines = []
                while line_index < len(lines) and lines[line_index].strip():
                    if keep_section:
                        trajectory_lines.append(lines[line_index])
                    line_index += 1
                line_index += 1
                if not keep_section:
                    continue

                # Collect the trajectory
                # Wait for client to be ready
                while not os.path.exists(os.path.join(client_folder, "ready")):
                    time.sleep(0.25)
                # Teleport client outside of the test area
                server.send_command(f"teleport {PLAYER_NAME} 0 2 -5 0 0")
                server.wait_regex(f".*?Teleported {PLAYER_NAME} to.*", 5)
                # Load structure block
                set_structure_block_command = "setblock 0 1 0 minecraft:structure_block"
                if version < "1.13":
                    set_structure_block_command += " 0 replace "
                set_structure_block_command += "{" + f"mode:LOAD,name:{structure_block_name},posX:0,posY:1,posZ:0,showboundingbox:1b" + "}"
                if version > "1.12.2":
                    set_structure_block_command += " replace"
                server.send_command(set_structure_block_command)
                server.wait_regex(".*: Changed the block at 0, 1, 0.*" if version > "1.12.2" else ".*: Block placed.*", 5)
                server.send_command(f"setblock 0 0 0 minecraft:redstone_block{' 0' if version < '1.13' else ''} replace")
                server.wait_regex(".*: Changed the block at 0, 0, 0.*" if version > "1.12.2" else ".*: Block placed.*", 5)

                # TP the player at the offset location
                server.send_command(f"teleport {PLAYER_NAME} {' '.join([str(p + float(o)) for p, o in zip([0, 2, 0, 0, 0], tp_offsets)])}")
                server.wait_regex(f".*?Teleported {PLAYER_NAME} to.*", 5)
                # Set gamemode to survival to reset any flying mode
                server.send_command(f"gamemode survival {PLAYER_NAME}")
                server.wait_regex(f".*? Set {PLAYER_NAME}'s game mode to.*", 5)
                # Execute any pre-run commands
                for command, regex in zip(commands_pre_run[::2], commands_pre_run[1::2]):
                    server.send_command(command.replace("${PLAYER_NAME}", PLAYER_NAME))
                    server.wait_regex(regex.replace("${PLAYER_NAME}", PLAYER_NAME), 5)
                # Wait for a couple of ticks to make sure it's registered
                # TODO: find a proper way to be sure?
                time.sleep(0.1)
                # Set gamemode to target one
                if gamemode != "survival":
                    server.send_command(f"gamemode {gamemode} {PLAYER_NAME}")
                    server.wait_regex(f".*? Set {PLAYER_NAME}'s game mode to.*", 5)
                    # Wait for a couple of ticks to make sure it's registered
                    # TODO: find a proper way to be sure?
                    time.sleep(0.1)

                # Create input file
                with open(os.path.join(client_folder, "inFile.csv.tmp"), "w") as f:
                    for line in trajectory_lines:
                        splitted = line.strip().split(";")
                        # Reorder the csv columns if necessary to be in the order expected by the patched client
                        f.write(";".join([splitted[csv_key_header.index(k)] for k in INPUTS_KEYS]) + "\n")
                os.rename(os.path.join(client_folder, "inFile.csv.tmp"), os.path.join(client_folder, "inFile.csv"))
                # Wait for input file to be removed (meaning output is ready)
                while os.path.exists(os.path.join(client_folder, "inFile.csv")):
                    time.sleep(0.25)

                # Add section to the out trajectory file
                with open(outpath, "a") as f:
                    f.write(section_name + "\n")
                    f.write(section_min_version + "\n")
                    f.write(section_max_version + "\n")
                    f.write(gamemode + "\n")
                    f.write(";".join(tp_offsets) + "\n")
                    f.write(";".join(commands_pre_run) + "\n")
                    f.write(";".join(commands_post_run) + "\n")
                    with open(os.path.join(client_folder, "outFile.csv"), "r") as fout:
                        for i, line in enumerate(fout):
                            if i == 0:
                                y_pos_index = line.strip().split(";").index("position.y")
                                f.write(line)
                            else:
                                splitted = line.strip().split(";")
                                # Change position.y to save the offset wrt the bottom right corner of the structure
                                # instead of the absolute position (structure block is at 0,1,0 with a posY of 1)
                                splitted[y_pos_index] = str(float(splitted[y_pos_index]) - 2.0)
                                f.write(";".join(splitted) + "\n")
                    f.write("\n")

                # Execute any post-run commands
                for command, regex in zip(commands_post_run[::2], commands_post_run[1::2]):
                    server.send_command(command.replace("${PLAYER_NAME}", PLAYER_NAME))
                    server.wait_regex(regex.replace("${PLAYER_NAME}", PLAYER_NAME), 5)
                # Cleanup for next iteration
                server.send_command(f"setblock 0 1 0 minecraft:air{' 0' if version < '1.13' else ''} replace")
                server.wait_regex(".*: Changed the block at 0, 1, 0.*" if version > "1.12.2" else ".*: Block placed.*", 5)
                server.send_command(f"setblock 0 0 0 minecraft:air{' 0' if version < '1.13' else ''} replace")
                server.wait_regex(".*: Changed the block at 0, 0, 0.*" if version > "1.12.2" else ".*: Block placed.*", 5)
                if gamemode != "creative":
                    server.send_command(f"gamemode creative {PLAYER_NAME}")
                    server.wait_regex(f".*? Set {PLAYER_NAME}'s game mode to.*", 5)
                server.send_command(f"effect {'give ' if version > '1.12.2' else ''}{PLAYER_NAME} regeneration 1 255")
                server.wait_regex(f".*?: .* to {PLAYER_NAME}.*")
                server.send_command(f"effect {'give ' if version > '1.12.2' else ''}{PLAYER_NAME} saturation 1 255")
                server.wait_regex(f".*?: .* to {PLAYER_NAME}.*")
                # Wait for a couple of ticks to make sure it's registered
                # TODO: find a proper way to be sure?
                time.sleep(0.1)
        print("Done!")
        result_queue.put(True)
    except Exception as e:
        print(e)
        result_queue.put(False)

def main(args):
    mc_version = args.version

    working_dir = args.build_folder
    os.makedirs(working_dir, exist_ok=True)

    manifest = download_file(MANIFEST_URL, working_dir, True)

    with open(manifest, "r") as f:
        manifest = json.load(f)
    if mc_version == "latest":
        mc_version = manifest["latest"]["release"]

    with open(os.path.join(working_dir, "version.txt"), "w") as f:
        f.write(mc_version)

    working_dir = os.path.join(working_dir, mc_version)
    os.makedirs(working_dir, exist_ok=True)

    version_manifest = download_file(next(filter(lambda x: x["id"] == mc_version, manifest["versions"]), None)["url"], working_dir, True)
    with open(version_manifest, "r") as f:
        version_manifest = json.load(f)

    server_folder = os.path.join(working_dir, "server")
    client_folder = os.path.join(working_dir, "client")

    # Make sure there is no leftover of a previous run
    if os.path.exists(os.path.join(args.output, mc_version)):
        shutil.rmtree(os.path.join(args.output, mc_version))
    if os.path.exists(os.path.join(server_folder, "world")):
        shutil.rmtree(os.path.join(server_folder, "world"))
    if os.path.exists(os.path.join(client_folder, "ready")):
        os.remove(os.path.join(client_folder, "ready"))
    if os.path.exists(os.path.join(client_folder, "inFile.csv")):
        os.remove(os.path.join(client_folder, "inFile.csv"))
    if os.path.exists(os.path.join(client_folder, "outFile.csv")):
        os.remove(os.path.join(client_folder, "outFile.csv"))

    # Start server
    server = Server(server_folder, version_manifest, args.dat, args.structures, args.java)

    # Start client
    try:
        client = setup_client(client_folder, version_manifest, args.patcher, args.java)
    except Exception as e:
        server.close()
        raise e

    try:
        collect_result = Queue()
        collect_thread = threading.Thread(target=collect_trajectories, args=(server, args.input, os.path.join(args.output, mc_version), client_folder, mc_version, collect_result), daemon=True)
        collect_thread.start()
        while collect_result.empty():
            # Client is still running
            if client.poll() is None:
                time.sleep(1)
                continue
            # Client has probably crashed
            if collect_result.empty():
                raise RuntimeError(f"Client closed while not done. Return code: {client.returncode}")
        if not collect_result.get():
            raise RuntimeError("Exception during trajectories collection")
    except Exception as e:
        client.terminate()
        server.close()
        raise e

    client.terminate()
    server.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="A program to generate vanilla results of all Botcraft physics tests")
    parser.add_argument("--version", "-v", help="Minecraft version", required=True)
    parser.add_argument("--build-folder", help="Working folder, all minecraft binaries will be downloaded and run in a version specific subfolder", default=".")
    parser.add_argument("--input", "-i", help="Input folder containing all the raw trajectories to generate", required=True)
    parser.add_argument("--output", "-o", help="Output folder where all processed trajectories will be generated", required=True)
    parser.add_argument("--structures", help="Path of the base folder containing all structure files", required=True)
    parser.add_argument("--dat", help="Path to a level.dat file to use for the server", default="")
    parser.add_argument("--patcher", help="Path to the java patcher file to apply before launching the client", default="ClientPatcher.java")
    parser.add_argument("--java", help="java executable called to patch the client and run the server (client will always use default Minecraft launcher JRE)", default="java")

    args = parser.parse_args()
    main(args)
