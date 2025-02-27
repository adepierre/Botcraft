import org.objectweb.asm.*;
import org.objectweb.asm.commons.AdviceAdapter;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;
import java.util.jar.JarFile;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ClientPatcher {
    // Keys to all classes, fields and methods we'll use/modify in the patch
    private static final String cLocalPlayer = "LocalPlayer";
    private static final String cEntity      = "Entity";
    private static final String cVec3        = "Vec3";
    private static final String cMinecraft   = "Minecraft";
    private static final String cOptions     = "Options";
    private static final String cKeyMapping  = "KeyMapping";
    private static final String fMinecraft   = "minecraft";
    private static final String fX           = "x";
    private static final String fY           = "y";
    private static final String fZ           = "z";
    private static final String fOptions     = "options";
    private static final String fKeyForward  = "keyUp";
    private static final String fKeyLeft     = "keyLeft";
    private static final String fKeyBackward = "keyDown";
    private static final String fKeyRight    = "keyRight";
    private static final String fKeyJump     = "keyJump";
    private static final String fKeySneak    = "keyShift";
    private static final String fKeySprint   = "keySprint";
    private static final String fIsDown      = "isDown";
    private static final String fOnGround    = "onGround";
    private static final String fYRot        = "yRot";
    private static final String fXRot        = "xRot";
    private static final String fNoRender    = "noRender";
    private static final String mTick        = "tick";
    private static final String mPosition    = "position";

    public static void main(String[] args) throws IOException {
        // Get the arguments
        String in_path = args[0];
        String out_path = args[1];
        String mappings = args[2];
        String version = args[3];

        initializeClasses(version);
        obfuscateClasses(mappings, version.compareTo("1.14.4") >= 0 /* version >= 1.14.4); */);

        Path inputJar = Paths.get(in_path);
        Path outputJar = Paths.get(out_path);

        try (JarInputStream jin = new JarInputStream(Files.newInputStream(inputJar));
             JarOutputStream jout = new JarOutputStream(Files.newOutputStream(outputJar))) {
            // Manually copy manifest as it's not part of jar entries
            Manifest manifest = jin.getManifest();
            if (manifest != null) {
                JarEntry manifestEntry = new JarEntry(JarFile.MANIFEST_NAME);
                jout.putNextEntry(manifestEntry);
                manifest.write(jout);
                jout.closeEntry();
            }

            JarEntry entry;
            while ((entry = jin.getNextJarEntry()) != null) {
                // Skip META-INF manifest as it was processed separately
                if (manifest != null && entry.getName().startsWith("META-INF/")
                        && !entry.isDirectory() && !entry.getName().equals(JarFile.MANIFEST_NAME)) {
                    continue;
                }

                // Modify LocalPlayer class to add pre and post tick custom functions
                if (entry.getName().equals(classes.get(cLocalPlayer).name + ".class")) {
                    byte[] classBytes = readClassBytes(jin);
                    byte[] modifiedBytes = modifyLocalPlayerClass(classBytes);

                    JarEntry newEntry = new JarEntry(entry.getName());
                    jout.putNextEntry(newEntry);
                    jout.write(modifiedBytes);
                    jout.closeEntry();
                }
                // Modify KeyMapping class to make sure isDown boolean is public
                else if (entry.getName().equals(classes.get(cKeyMapping).name + ".class")) {
                    byte[] classBytes = readClassBytes(jin);
                    byte[] modifiedBytes = modifyKeyMappingClass(classBytes);

                    JarEntry newEntry = new JarEntry(entry.getName());
                    jout.putNextEntry(newEntry);
                    jout.write(modifiedBytes);
                    jout.closeEntry();
                }
                // Modify Entity class to make sure onGround boolean, and x/yRot floats are public
                else if (entry.getName().equals(classes.get(cEntity).name + ".class")) {
                    byte[] classBytes = readClassBytes(jin);
                    byte[] modifiedBytes = modifyEntityClass(classBytes);

                    JarEntry newEntry = new JarEntry(entry.getName());
                    jout.putNextEntry(newEntry);
                    jout.write(modifiedBytes);
                    jout.closeEntry();
                }
                // Just copy the class as it is
                else {
                    // Copy unchanged entries
                    copyEntry(jin, jout, entry);
                    continue;
                }
            }
        }
    }

    private static class ObfuscatedClass {
        public String name;
        public Map<String, String> fields;
        public Map<String, String> methods;
        public ObfuscatedClass(String name, Map<String, String> fields, Map<String, String> methods) {
            this.name = name;
            this.fields = fields;
            this.methods = methods;
        }
    }
    private static Map<String, ObfuscatedClass> classes = new HashMap<>();

    // Map all the keys to their corresponding non-obfuscated names, while defining the class/fields/methods structure
    private static void initializeClasses(String version) {
        final boolean isMojangMapping = version.compareTo("1.14.4") >= 0; // version >= 1.14.4
        classes.clear();
        classes.put(
            cLocalPlayer, new ObfuscatedClass(
                    isMojangMapping ?
                        "net.minecraft.client.player.LocalPlayer" :
                        version.compareTo("1.14") < 0 /* version < 1.14 */ ?
                            "net/minecraft/client/entity/EntityPlayerSP" :
                            "net/minecraft/client/entity/player/ClientPlayerEntity",
                    new HashMap<>(Map.of(fMinecraft, isMojangMapping ? "minecraft" : "field_71159_c")),
                    new HashMap<>(Map.of(mTick, isMojangMapping ? "tick" : "func_70071_h_"))
            )
        );
        classes.put(
            cEntity, new ObfuscatedClass(
                    isMojangMapping ? "net.minecraft.world.entity.Entity" : "net/minecraft/entity/Entity",
                    new HashMap<>(Map.of(
                        fOnGround, isMojangMapping ? "onGround" : "field_70122_E",
                        fXRot,     isMojangMapping ? "xRot"     : "field_70125_A",
                        fYRot,     isMojangMapping ? "yRot"     : "field_70177_z")),
                    new HashMap<>(Map.of(mPosition, isMojangMapping ? "position" : "func_174791_d"))
            )
        );
        classes.put(
            cVec3, new ObfuscatedClass(
                    isMojangMapping ? "net.minecraft.world.phys.Vec3" : "net/minecraft/util/math/Vec3d",
                    new HashMap<>(Map.of(
                            fX, isMojangMapping ? "x" : "field_72450_a",
                            fY, isMojangMapping ? "y" : "field_72448_b",
                            fZ, isMojangMapping ? "z" : "field_72449_c")),
                    new HashMap<>()
            )
        );
        classes.put(
            cMinecraft, new ObfuscatedClass(
                    isMojangMapping ? "net.minecraft.client.Minecraft" : "net/minecraft/client/Minecraft",
                    new HashMap<>(Map.of(fOptions, isMojangMapping ? "options" : "field_71474_y")),
                    new HashMap<>()
            )
        );
        classes.put(
            cOptions, new ObfuscatedClass(
                    isMojangMapping ? "net.minecraft.client.Options" : "net/minecraft/client/settings/GameSettings",
                    new HashMap<>(Map.of(
                            fKeyForward,  isMojangMapping ? "keyUp"     : "field_74351_w",
                            fKeyLeft,     isMojangMapping ? "keyLeft"   : "field_74370_x",
                            fKeyBackward, isMojangMapping ? "keyDown"   : "field_74368_y",
                            fKeyRight,    isMojangMapping ? "keyRight"  : "field_74366_z",
                            fKeyJump,     isMojangMapping ? "keyJump"   : "field_74314_A",
                            fKeySneak,    isMojangMapping ? "keyShift"  : "field_74311_E",
                            fKeySprint,   isMojangMapping ? "keySprint" : "field_151444_V"
                    )),
                    new HashMap<>()
            )
        );
        classes.put(
            cKeyMapping, new ObfuscatedClass(
                    isMojangMapping ? "net.minecraft.client.KeyMapping" : "net/minecraft/client/settings/KeyBinding",
                    new HashMap<>(Map.of(fIsDown, isMojangMapping ? "isDown" : "field_74513_e")),
                    new HashMap<>() // We don't need get/set methods for KeyMapping, we'll set isDown field to public instead
            )
        );
    }

    // Retrieve the obfuscated names of all classes, fields and methods we need from a mapping file
    private static void obfuscateClasses(String mappings, boolean isMojangMapping) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(mappings));
        String line;
        String currentClass = null;
        boolean checkClassContent = false;
        Pattern classPattern = Pattern.compile(
                isMojangMapping ?
                    "^(.*) -> (.*):$" :
                    "^([^\\s-]*) ([^\\s-]*)$"
        );
        Pattern methodPattern = Pattern.compile(
                isMojangMapping ?
                    "^\\s+[0-9]+:[0-9]+:(.*) (.*)\\(.*\\) -> (.*)$" :
                    "^\\s+(.*) \\(.*\\)(.*) (func_.*)$"
        );
        Pattern fieldPattern = Pattern.compile(
                isMojangMapping ?
                    "^\\s+(.*) (.*) -> (.*)$" :
                    "^\\s+(.*) (field_.*)$"
        );
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("#")) {
                continue;
            }

            Matcher matcher = classPattern.matcher(line);
            if (matcher.matches()) {
                final int obfNameIndex = isMojangMapping ? 2 : 1;
                final int clearNameIndex = isMojangMapping ? 1 : 2;

                String clearName = matcher.group(clearNameIndex);
                checkClassContent = false;
                for (var entry : classes.entrySet()) {
                    if (entry.getValue().name.equals(clearName)) {
                        // System.out.println("Class: " + entry.getValue().name + " obfuscated is: " + matcher.group(obfNameIndex));
                        entry.getValue().name = matcher.group(obfNameIndex);
                        currentClass = entry.getKey();
                        checkClassContent = true;
                    }
                }

                continue;
            }

            if (!checkClassContent) {
                continue;
            }

            // Methods need to be before fields to prevent fields pattern to match methods lines as we don't specify descriptors
            matcher = methodPattern.matcher(line);
            if (matcher.matches()) {
                final int obfNameIndex = isMojangMapping ? 3 : 1;
                final int plainNameIndex = isMojangMapping ? 2 : 3;

                for (var entry : classes.get(currentClass).methods.entrySet()) {
                    if (matcher.group(plainNameIndex).equals(entry.getValue())) {
                        // System.out.println("\tMethod: " + entry.getValue() + " obfuscated is: " + matcher.group(obfNameIndex));
                        entry.setValue(matcher.group(obfNameIndex));
                    }
                }
                continue;
            }

            matcher = fieldPattern.matcher(line);
            if (matcher.matches()) {
                final int obfNameIndex = isMojangMapping ? 3 : 1;
                for (var entry : classes.get(currentClass).fields.entrySet()) {
                    if (matcher.group(2).equals(entry.getValue())) {
                        // System.out.println("\tField: " + entry.getValue() + " obfuscated is: " + matcher.group(obfNameIndex));
                        entry.setValue(matcher.group(obfNameIndex));
                    }
                }
            }
        }
    }

    private static byte[] readClassBytes(InputStream in) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        byte[] buffer = new byte[4096];
        int bytesRead;
        while ((bytesRead = in.read(buffer)) != -1) {
            bos.write(buffer, 0, bytesRead);
        }
        return bos.toByteArray();
    }

    private static void copyEntry(JarInputStream jin, JarOutputStream jout, JarEntry entry) throws IOException {
        jout.putNextEntry(new JarEntry(entry));
        byte[] buffer = new byte[4096];
        int bytesRead;
        while ((bytesRead = jin.read(buffer)) != -1) {
            jout.write(buffer, 0, bytesRead);
        }
        jout.closeEntry();
    }

    private static byte[] modifyLocalPlayerClass(byte[] classBytes) {
        ClassReader cr = new ClassReader(classBytes);
        // COMPUTE_FRAMES to automatically compute frames and maxs thing
        ClassWriter cw = new ClassWriter(cr, ClassWriter.COMPUTE_FRAMES);
        cr.accept(new LocalPlayerClassVisitor(cw), ClassReader.EXPAND_FRAMES);
        return cw.toByteArray();
    }

    // Names of static field we add to the LocalPlayer class
    private final static String tickCounter = "tickCounter";
    private final static String inFile = "inFile";
    private final static String outFile = "outFile";
    private final static String readyFile = "ready";

    private static class LocalPlayerClassVisitor extends ClassVisitor {
        public LocalPlayerClassVisitor(ClassVisitor cv) {
            super(Opcodes.ASM9, cv);
        }

        @Override
        public void visit(int version, int access, String name, String signature, String superName, String[] interfaces) {
            super.visit(version, access, name, signature, superName, interfaces);
        }

        @Override
        public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
            MethodVisitor mv = cv.visitMethod(access, name, descriptor, signature, exceptions);

            if (classes.get(cLocalPlayer).methods.get(mTick).equals(name) && "()V".equals(descriptor)) {
                return new TickMethodVisitor(Opcodes.ASM9, mv, access, name, descriptor);
            }

            return mv;
        }

        @Override
        public void visitEnd() {
            // Add "tickCounter" static field
            cv.visitField(
                Opcodes.ACC_PRIVATE | Opcodes.ACC_STATIC,
                tickCounter,
                "I",
                null,
                -1
            );

            // Add "inFile" static field
            cv.visitField(
                Opcodes.ACC_PRIVATE | Opcodes.ACC_STATIC,
                inFile,
                "Ljava/io/BufferedReader;",
                null,
                null
            );

            // Add "outFile" static field
            cv.visitField(
                Opcodes.ACC_PRIVATE | Opcodes.ACC_STATIC,
                outFile,
                "Ljava/io/BufferedWriter;",
                null,
                null
            );

            cv.visitEnd();
        }
    }

    private static class TickMethodVisitor extends AdviceAdapter {
        public TickMethodVisitor(int api, MethodVisitor mv, int access, String name, String descriptor) {
            super(api, mv, access, name, descriptor);
        }

        private void setKeyDown(String key, boolean value) {
            // this.minecraft.options.<key>.isDown = <value>;
            mv.visitVarInsn(ALOAD, 0);
            mv.visitFieldInsn(GETFIELD, classes.get(cLocalPlayer).name, classes.get(cLocalPlayer).fields.get(fMinecraft), "L" + classes.get(cMinecraft).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cMinecraft).name, classes.get(cMinecraft).fields.get(fOptions), "L" + classes.get(cOptions).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cOptions).name, classes.get(cOptions).fields.get(key), "L" + classes.get(cKeyMapping).name + ";");
            mv.visitInsn(value ? ICONST_1 : ICONST_0);
            mv.visitFieldInsn(PUTFIELD, classes.get(cKeyMapping).name, classes.get(cKeyMapping).fields.get(fIsDown), "Z");
        }

        private void setKeyDownFromStringArray(String key, int stringArrayVariable, int index) {
            // this.minecraft.options.<key>.isDown = Integer.parseInt(<stringArrayVariable>[<index>].trim()) != 0;
            mv.visitVarInsn(ALOAD, 0);
            mv.visitFieldInsn(GETFIELD, classes.get(cLocalPlayer).name, classes.get(cLocalPlayer).fields.get(fMinecraft), "L" + classes.get(cMinecraft).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cMinecraft).name, classes.get(cMinecraft).fields.get(fOptions), "L" + classes.get(cOptions).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cOptions).name, classes.get(cOptions).fields.get(key), "L" + classes.get(cKeyMapping).name + ";");
            mv.visitVarInsn(ALOAD, stringArrayVariable);
            // for int < 5 there is a smaller predefined const, so use it
            if (index > -1 && index < 5) {
                switch (index) {
                    case 0: mv.visitInsn(ICONST_0); break;
                    case 1: mv.visitInsn(ICONST_1); break;
                    case 2: mv.visitInsn(ICONST_2); break;
                    case 3: mv.visitInsn(ICONST_3); break;
                    case 4: mv.visitInsn(ICONST_4); break;
                    case 5: mv.visitInsn(ICONST_5); break;
                }
            }
            // otherwise, just use bipush with the constant
            else {
                mv.visitIntInsn(BIPUSH, index);
            }
            mv.visitInsn(AALOAD);
            mv.visitMethodInsn(INVOKEVIRTUAL, "java/lang/String", "trim", "()Ljava/lang/String;", false);
            mv.visitMethodInsn(INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", false);
            Label label_case_0 = new Label();
            Label label_end_check = new Label();
            // if != 0
            mv.visitJumpInsn(IFEQ, label_case_0);
                mv.visitInsn(ICONST_1);
                mv.visitJumpInsn(GOTO, label_end_check);
            // else
                mv.visitLabel(label_case_0);
                mv.visitInsn(ICONST_0);
            mv.visitLabel(label_end_check);
            mv.visitFieldInsn(PUTFIELD, classes.get(cKeyMapping).name, classes.get(cKeyMapping).fields.get(fIsDown), "Z");
        }

        private void writeKeyStateToOutFile(String key, boolean withSemiColon) {
            // outFile.write(this.minecraft.options.<key>.isDown ? "1" : "0");
            mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
            mv.visitVarInsn(ALOAD, 0);
            mv.visitFieldInsn(GETFIELD, classes.get(cLocalPlayer).name, classes.get(cLocalPlayer).fields.get(fMinecraft), "L" + classes.get(cMinecraft).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cMinecraft).name, classes.get(cMinecraft).fields.get(fOptions), "L" + classes.get(cOptions).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cOptions).name, classes.get(cOptions).fields.get(key), "L" + classes.get(cKeyMapping).name + ";");
            mv.visitFieldInsn(GETFIELD, classes.get(cKeyMapping).name, classes.get(cKeyMapping).fields.get(fIsDown), "Z");
            Label label_case_false = new Label();
            Label label_end_check = new Label();
            // if b
            mv.visitJumpInsn(IFEQ, label_case_false);
                mv.visitLdcInsn("1");
                mv.visitJumpInsn(GOTO, label_end_check);
            // else
                mv.visitLabel(label_case_false);
                mv.visitLdcInsn("0");
            mv.visitLabel(label_end_check);
            mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
            if (withSemiColon) {
                // outFile.write(";")
                mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                mv.visitLdcInsn(";");
                mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
            }
        }

        private void printString(String s) {
            mv.visitFieldInsn(GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
            mv.visitLdcInsn(s);
            mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V", false);
        }

        @Override
        protected void onMethodEnter() {
            // try
            Label labelTryStart = new Label();
            Label labelTryEnd = new Label();
            Label labelCatchStart = new Label();
            mv.visitTryCatchBlock(labelTryStart, labelTryEnd, labelCatchStart, "java/io/IOException");
            mv.visitLabel(labelTryStart);
                Label labelIfTickCounterEnd = new Label();
                Label labelElseInFileNullEnd = new Label();
                // if (tickCounter == -1)
                mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, tickCounter, "I");
                mv.visitInsn(ICONST_M1);
                mv.visitJumpInsn(IF_ICMPNE, labelIfTickCounterEnd);
                    // Files.createFile(Paths.get("ready"));
                    mv.visitLdcInsn(readyFile);
                    mv.visitInsn(ICONST_0);
                    mv.visitTypeInsn(ANEWARRAY, "java/lang/String");
                    mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Paths", "get", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/nio/file/Path;", false);
                    mv.visitInsn(ICONST_0);
                    mv.visitTypeInsn(ANEWARRAY, "java/nio/file/attribute/FileAttribute");
                    mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Files", "createFile", "(Ljava/nio/file/Path;[Ljava/nio/file/attribute/FileAttribute;)Ljava/nio/file/Path;", false);
                    mv.visitInsn(POP);
                    // tickCounter = 0;
                    mv.visitInsn(ICONST_0);
                    mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, tickCounter, "I");
                    // Skip else branch
                    mv.visitJumpInsn(GOTO, labelElseInFileNullEnd);
                mv.visitLabel(labelIfTickCounterEnd);
                // else if (inFile == null)
                mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, inFile, "Ljava/io/BufferedReader;");
                mv.visitJumpInsn(IFNONNULL, labelElseInFileNullEnd);
                    // if (Files.exists(Paths.get("inFile.csv")))
                    mv.visitLdcInsn(inFile + ".csv");
                    mv.visitInsn(ICONST_0);
                    mv.visitTypeInsn(ANEWARRAY, "java/lang/String");
                    mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Paths", "get", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/nio/file/Path;", false);
                    mv.visitInsn(ICONST_0);
                    mv.visitTypeInsn(ANEWARRAY, "java/nio/file/LinkOption");
                    mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Files", "exists", "(Ljava/nio/file/Path;[Ljava/nio/file/LinkOption;)Z", false);
                    mv.visitJumpInsn(IFEQ, labelElseInFileNullEnd);
                        // inFile = new BufferedReader(new FileReader("inFile.csv"));
                        mv.visitTypeInsn(NEW, "java/io/BufferedReader");
                        mv.visitInsn(DUP);
                        mv.visitTypeInsn(NEW, "java/io/FileReader");
                        mv.visitInsn(DUP);
                        mv.visitLdcInsn(inFile + ".csv");
                        mv.visitMethodInsn(INVOKESPECIAL, "java/io/FileReader", "<init>", "(Ljava/lang/String;)V", false);
                        mv.visitMethodInsn(INVOKESPECIAL, "java/io/BufferedReader", "<init>", "(Ljava/io/Reader;)V", false);
                        mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, inFile, "Ljava/io/BufferedReader;");
                        // outFile = new BufferedWriter(new FileWriter("outFile.csv"));
                        mv.visitTypeInsn(NEW, "java/io/BufferedWriter");
                        mv.visitInsn(DUP);
                        mv.visitTypeInsn(NEW, "java/io/FileWriter");
                        mv.visitInsn(DUP);
                        mv.visitLdcInsn(outFile + ".csv");
                        mv.visitMethodInsn(INVOKESPECIAL, "java/io/FileWriter", "<init>", "(Ljava/lang/String;)V", false);
                        mv.visitMethodInsn(INVOKESPECIAL, "java/io/BufferedWriter", "<init>", "(Ljava/io/Writer;)V", false);
                        mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                        // outFile.write("forward;left;backward;right;jump;sneak;sprint;yRot;xRot;position.x;position.y;position.z;onGround\n")
                        mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                        mv.visitLdcInsn("forward;left;backward;right;jump;sneak;sprint;yRot;xRot;position.x;position.y;position.z;onGround\n");
                        mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                        // Files.delete(Paths.get("ready"));
                        mv.visitLdcInsn(readyFile);
                        mv.visitInsn(ICONST_0);
                        mv.visitTypeInsn(ANEWARRAY, "java/lang/String");
                        mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Paths", "get", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/nio/file/Path;", false);
                        mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Files", "delete", "(Ljava/nio/file/Path;)V", false);
                mv.visitLabel(labelElseInFileNullEnd);
                // Reset all key press states to false
                setKeyDown(fKeyForward, false);
                setKeyDown(fKeyLeft, false);
                setKeyDown(fKeyBackward, false);
                setKeyDown(fKeyRight, false);
                setKeyDown(fKeyJump, false);
                setKeyDown(fKeySneak, false);
                setKeyDown(fKeySprint, false);
                // if (inFile != null)
                mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, inFile, "Ljava/io/BufferedReader;");
                mv.visitJumpInsn(IFNULL, labelTryEnd);
                    int line = newLocal(Type.getType("Ljava/lang/String;"));
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, inFile, "Ljava/io/BufferedReader;");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedReader", "readLine", "()Ljava/lang/String;", false);
                    mv.visitVarInsn(ASTORE, line);
                    // if (line == null)
                    mv.visitVarInsn(ALOAD, line);
                    Label labelIfLineNullEnd = new Label();
                    mv.visitJumpInsn(IFNONNULL, labelIfLineNullEnd);
                        // infFile.close();
                        mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, inFile, "Ljava/io/BufferedReader;");
                        mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedReader", "close", "()V", false);
                        // inFile = null;
                        mv.visitInsn(ACONST_NULL);
                        mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, inFile, "Ljava/io/BufferedReader;");
                        // outFile.close();
                        mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                        mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "close", "()V", false);
                        // outFile = null;
                        mv.visitInsn(ACONST_NULL);
                        mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                        // Files.delete(Paths.get("inFile.csv"));
                        mv.visitLdcInsn(inFile + ".csv");
                        mv.visitInsn(ICONST_0);
                        mv.visitTypeInsn(ANEWARRAY, "java/lang/String");
                        mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Paths", "get", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/nio/file/Path;", false);
                        mv.visitMethodInsn(INVOKESTATIC, "java/nio/file/Files", "delete", "(Ljava/nio/file/Path;)V", false);
                        // tickCounter = -1;
                        mv.visitInsn(ICONST_M1);
                        mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, tickCounter, "I");
                        // Skip else branch
                        mv.visitJumpInsn(GOTO, labelTryEnd);
                    mv.visitLabel(labelIfLineNullEnd);
                    // else
                        // String[] splitted = line.split(";");
                        int splitted = newLocal(Type.getType("[Ljava/lang/String;"));
                        mv.visitVarInsn(ALOAD, line);
                        mv.visitLdcInsn(";");
                        mv.visitMethodInsn(INVOKEVIRTUAL, "java/lang/String", "split", "(Ljava/lang/String;)[Ljava/lang/String;", false);
                        mv.visitVarInsn(ASTORE, splitted);
                        // parse the csv line and set the keys to the right values
                        setKeyDownFromStringArray(fKeyForward, splitted, 0);
                        setKeyDownFromStringArray(fKeyLeft, splitted, 1);
                        setKeyDownFromStringArray(fKeyBackward, splitted, 2);
                        setKeyDownFromStringArray(fKeyRight, splitted, 3);
                        setKeyDownFromStringArray(fKeyJump, splitted, 4);
                        setKeyDownFromStringArray(fKeySneak, splitted, 5);
                        setKeyDownFromStringArray(fKeySprint, splitted, 6);
                        // this.yRot = Float.parseFloat(values[7].trim());
                        mv.visitVarInsn(ALOAD, 0);
                        mv.visitVarInsn(ALOAD, splitted);
                        mv.visitVarInsn(BIPUSH, 7);
                        mv.visitInsn(AALOAD);
                        mv.visitMethodInsn(INVOKEVIRTUAL, "java/lang/String", "trim", "()Ljava/lang/String;", false);
                        mv.visitMethodInsn(INVOKESTATIC, "java/lang/Float", "parseFloat", "(Ljava/lang/String;)F", false);
                        mv.visitFieldInsn(PUTFIELD, classes.get(cEntity).name, classes.get(cEntity).fields.get(fYRot), "F");
                        // this.xRot = Float.parseFloat(values[8].trim());
                        mv.visitVarInsn(ALOAD, 0);
                        mv.visitVarInsn(ALOAD, splitted);
                        mv.visitVarInsn(BIPUSH, 8);
                        mv.visitInsn(AALOAD);
                        mv.visitMethodInsn(INVOKEVIRTUAL, "java/lang/String", "trim", "()Ljava/lang/String;", false);
                        mv.visitMethodInsn(INVOKESTATIC, "java/lang/Float", "parseFloat", "(Ljava/lang/String;)F", false);
                        mv.visitFieldInsn(PUTFIELD, classes.get(cEntity).name, classes.get(cEntity).fields.get(fXRot), "F");
                        // tickCounter += 1;
                        mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, tickCounter, "I");
                        mv.visitInsn(ICONST_1);
                        mv.visitInsn(IADD);
                        mv.visitFieldInsn(PUTSTATIC, classes.get(cLocalPlayer).name, tickCounter, "I");
            mv.visitLabel(labelTryEnd);
            Label labelCatchEnd = new Label();
            mv.visitJumpInsn(GOTO, labelCatchEnd);
            // Catch(IOException e)
            mv.visitLabel(labelCatchStart);
            int exception = newLocal(Type.getType("Ljava/io/IOException;"));
            mv.visitVarInsn(ASTORE, exception);
                // e.printStackTrace();
                mv.visitVarInsn(ALOAD, exception);
                mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/IOException", "printStackTrace", "()V", false);
            mv.visitLabel(labelCatchEnd);
        }

        @Override
        protected void onMethodExit(int opcode) {
            Label labelTryStart = new Label();
            Label labelTryEnd = new Label();
            Label labelCatchStart = new Label();
            mv.visitTryCatchBlock(labelTryStart, labelTryEnd, labelCatchStart, "java/io/IOException");
            // try
            mv.visitLabel(labelTryStart);
                // if (outFile != null)
                mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                mv.visitJumpInsn(IFNULL, labelTryEnd);
                    // Write all key status
                    writeKeyStateToOutFile(fKeyForward, true);
                    writeKeyStateToOutFile(fKeyLeft, true);
                    writeKeyStateToOutFile(fKeyBackward, true);
                    writeKeyStateToOutFile(fKeyRight, true);
                    writeKeyStateToOutFile(fKeyJump, true);
                    writeKeyStateToOutFile(fKeySneak, true);
                    writeKeyStateToOutFile(fKeySprint, true);
                    // outFile.write(Float.toString(this.yRot));
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitVarInsn(ALOAD, 0);
                    mv.visitFieldInsn(GETFIELD, classes.get(cEntity).name, classes.get(cEntity).fields.get(fYRot), "F");
                    mv.visitMethodInsn(INVOKESTATIC, "java/lang/Float", "toString", "(F)Ljava/lang/String;", false);
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(";")
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitLdcInsn(";");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(Float.toString(this.xRot));
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitVarInsn(ALOAD, 0);
                    mv.visitFieldInsn(GETFIELD, classes.get(cEntity).name, classes.get(cEntity).fields.get(fXRot), "F");
                    mv.visitMethodInsn(INVOKESTATIC, "java/lang/Float", "toString", "(F)Ljava/lang/String;", false);
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(";")
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitLdcInsn(";");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(Double.toString(this.position().x));
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitVarInsn(ALOAD, 0);
                    mv.visitMethodInsn(INVOKEVIRTUAL, classes.get(cLocalPlayer).name, classes.get(cEntity).methods.get(mPosition), "()L" + classes.get(cVec3).name + ";", false);
                    mv.visitFieldInsn(GETFIELD, classes.get(cVec3).name, classes.get(cVec3).fields.get(fX), "D");
                    mv.visitMethodInsn(INVOKESTATIC, "java/lang/Double", "toString", "(D)Ljava/lang/String;", false);
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(";")
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitLdcInsn(";");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(Double.toString(this.position().y));
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitVarInsn(ALOAD, 0);
                    mv.visitMethodInsn(INVOKEVIRTUAL, classes.get(cLocalPlayer).name, classes.get(cEntity).methods.get(mPosition), "()L" + classes.get(cVec3).name + ";", false);
                    mv.visitFieldInsn(GETFIELD, classes.get(cVec3).name, classes.get(cVec3).fields.get(fY), "D");
                    mv.visitMethodInsn(INVOKESTATIC, "java/lang/Double", "toString", "(D)Ljava/lang/String;", false);
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(";")
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitLdcInsn(";");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(Double.toString(this.position().z));
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitVarInsn(ALOAD, 0);
                    mv.visitMethodInsn(INVOKEVIRTUAL, classes.get(cLocalPlayer).name, classes.get(cEntity).methods.get(mPosition), "()L" + classes.get(cVec3).name + ";", false);
                    mv.visitFieldInsn(GETFIELD, classes.get(cVec3).name, classes.get(cVec3).fields.get(fZ), "D");
                    mv.visitMethodInsn(INVOKESTATIC, "java/lang/Double", "toString", "(D)Ljava/lang/String;", false);
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(";")
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitLdcInsn(";");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write(this.onGround ? "1" : "0");
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitVarInsn(ALOAD, 0);
                    mv.visitFieldInsn(GETFIELD, classes.get(cEntity).name, classes.get(cEntity).fields.get(fOnGround), "Z");
                    Label labelOnGroundFalse = new Label();
                    Label labelOnGroundCheck = new Label();
                    // if OnGround
                    mv.visitJumpInsn(IFEQ, labelOnGroundFalse);
                        mv.visitLdcInsn("1");
                        mv.visitJumpInsn(GOTO, labelOnGroundCheck);
                    // else
                        mv.visitLabel(labelOnGroundFalse);
                        mv.visitLdcInsn("0");
                    mv.visitLabel(labelOnGroundCheck);
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
                    // outFile.write("\n")
                    mv.visitFieldInsn(GETSTATIC, classes.get(cLocalPlayer).name, outFile, "Ljava/io/BufferedWriter;");
                    mv.visitLdcInsn("\n");
                    mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/BufferedWriter", "write", "(Ljava/lang/String;)V", false);
            mv.visitLabel(labelTryEnd);
            Label labelCatchEnd = new Label();
            mv.visitJumpInsn(GOTO, labelCatchEnd);
            // Catch(IOException e)
            mv.visitLabel(labelCatchStart);
            int exception = newLocal(Type.getType("Ljava/io/IOException;"));
            mv.visitVarInsn(ASTORE, exception);
                // e.printStackTrace();
                mv.visitVarInsn(ALOAD, exception);
                mv.visitMethodInsn(INVOKEVIRTUAL, "java/io/IOException", "printStackTrace", "()V", false);
            mv.visitLabel(labelCatchEnd);
        }
    }



    private static byte[] modifyKeyMappingClass(byte[] classBytes) {
        ClassReader cr = new ClassReader(classBytes);
        ClassWriter cw = new ClassWriter(cr, ClassWriter.COMPUTE_FRAMES);
        cr.accept(new KeyMappingClassVisitor(cw), ClassReader.EXPAND_FRAMES);
        return cw.toByteArray();
    }

    private static class KeyMappingClassVisitor extends ClassVisitor {
        public KeyMappingClassVisitor(ClassVisitor cv) {
            super(Opcodes.ASM9, cv);
        }

        @Override
        public FieldVisitor visitField(int access, String name, String descriptor, String signature, Object value) {
            if (classes.get(cKeyMapping).fields.get(fIsDown).equals(name)) {
                return super.visitField(Opcodes.ACC_PUBLIC, name, descriptor, signature, value);
            }

            return super.visitField(access, name, descriptor, signature, value);
        }
    }


    private static byte[] modifyEntityClass(byte[] classBytes) {
        ClassReader cr = new ClassReader(classBytes);
        // COMPUTE_FRAMES to automatically compute frames and maxs thing
        ClassWriter cw = new ClassWriter(cr, ClassWriter.COMPUTE_FRAMES);
        cr.accept(new EntityClassVisitor(cw), ClassReader.EXPAND_FRAMES);
        return cw.toByteArray();
    }

    private static class EntityClassVisitor extends ClassVisitor {
        public EntityClassVisitor(ClassVisitor cv) {
            super(Opcodes.ASM9, cv);
        }

        @Override
        public FieldVisitor visitField(int access, String name, String descriptor, String signature, Object value) {
            if (classes.get(cEntity).fields.get(fOnGround).equals(name) ||
                classes.get(cEntity).fields.get(fXRot).equals(name) ||
                classes.get(cEntity).fields.get(fYRot).equals(name)) {
                return super.visitField(Opcodes.ACC_PUBLIC, name, descriptor, signature, value);
            }

            return super.visitField(access, name, descriptor, signature, value);
        }
    }
}
