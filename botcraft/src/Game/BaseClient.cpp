#include <functional>

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Inventory.hpp"
#include "botcraft/Game/BaseClient.hpp"

#include "botcraft/Network/Compression.hpp"
#include "botcraft/Network/TCP_Com.hpp"
#include "botcraft/Network/Authentifier.hpp"
#include "botcraft/Network/AESEncrypter.hpp"

#include "botcraft/Protocol/MessageFactory.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    BaseClient::BaseClient(const bool afk_only_, const std::vector<int> &printed_packets_)
    {
        afk_only = afk_only_;
        state = State::None;
        game_mode = GameMode::None;
        dimension = Dimension::None;
        difficulty = Difficulty::None;
        is_hardcore = false;
#if PROTOCOL_VERSION > 463
        difficulty_locked = true;
#endif

        player = nullptr;
        world = nullptr;
        inventory_manager = nullptr;
        com = nullptr;
        authentifier = nullptr;

#if USE_GUI
        renderer = nullptr;
#endif

        printed_packets = std::vector<bool>(80, false);
        for (int i = 0; i < printed_packets_.size(); ++i)
        {
            printed_packets[printed_packets_[i]] = true;
        }

        auto_respawn = false;

        should_be_closed = false;

        compression = -1;

        // Ensure the assets are loaded
        AssetsManager::getInstance();
    }

    BaseClient::~BaseClient()
    {
        Disconnect();
    }

    void BaseClient::Connect(const std::string &ip, const unsigned int port, const std::string &login, const std::string &password)
    {
        state = State::Handshaking;

        //Start the thread to process the incoming packets
        m_thread_process = std::thread(&BaseClient::WaitForNewPackets, this);

        com = std::shared_ptr<TCP_Com>(new TCP_Com(ip, port, std::bind(&BaseClient::OnNewPacket, this, std::placeholders::_1)));
        
        //Let some time to initialize the communication before actually send data
        // TODO: make this in a cleaner way?
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::shared_ptr<Handshake> handshake_msg(new Handshake);
        handshake_msg->SetProtocolVersion(PROTOCOL_VERSION);
        handshake_msg->SetServerAddress(ip);
        handshake_msg->SetServerPort(port);
        handshake_msg->SetNextState((int)State::Login);
        Send(handshake_msg);

        state = State::Login;

        // Offline mode case
        if (password == "")
        {
            name = login;
        }
        // Online mode case
        else
        {
            authentifier = std::shared_ptr<Authentifier>(new Authentifier());
            if (!authentifier->AuthToken(login, password))
            {
                throw std::runtime_error("Error trying to authenticate on Mojang server");
            }
            name = authentifier->GetPlayerDisplayName();
        }

        std::shared_ptr<LoginStart> loginstart_msg(new LoginStart);
        loginstart_msg->SetName(name);
        Send(loginstart_msg);
    }

    void BaseClient::Send(const std::shared_ptr<Message> msg)
    {
        if (com)
        {
            std::vector<unsigned char> msg_data;
            msg->Write(msg_data);
            if (compression == -1)
            {
                com->SendPacket(msg_data);
            }
            else
            {
#ifdef USE_COMPRESSION
                if (msg_data.size() < compression)
                {
                    msg_data.insert(msg_data.begin(), 0x00);
                    com->SendPacket(msg_data);
                }
                else
                {
                    std::vector<unsigned char> compressed_msg;
                    WriteVarInt(msg_data.size(), compressed_msg);
                    std::vector<unsigned char> compressed_data = Compress(msg_data);
                    compressed_msg.insert(compressed_msg.end(), compressed_data.begin(), compressed_data.end());
                    com->SendPacket(compressed_msg);
                }
#else
                throw(std::runtime_error("Program compiled without ZLIB. Cannot send compressed message"));
#endif
            }
        }
    }

    void BaseClient::WaitForNewPackets()
    {
        while (state != State::None)
        {
            {
                std::unique_lock<std::mutex> lck(mutex_process);
                process_condition.wait(lck);
            }
            while (!packets_to_process.empty())
            {
                std::vector<unsigned char> packet;
                { // process_guard scope
                    std::lock_guard<std::mutex> process_guard(mutex_process);
                    if (!packets_to_process.empty())
                    {
                        packet = packets_to_process.front();
                        packets_to_process.pop_front();
                    }
                }
                if (packet.size() > 0)
                {
                    if (compression == -1)
                    {
                        ProcessPacket(packet);
                    }
                    else
                    {
#ifdef USE_COMPRESSION
                        size_t length = packet.size();
                        ReadIterator iter = packet.begin();
                        int data_length = ReadVarInt(iter, length);

                        //Packet not compressed
                        if (data_length == 0)
                        {
                            //Erase the first 0
                            packet.erase(packet.begin());
                            ProcessPacket(packet);
                        }
                        //Packet compressed
                        else
                        {
                            int size_varint = packet.size() - length;

                            std::vector<unsigned char> uncompressed_msg = Decompress(packet, size_varint);
                            ProcessPacket(uncompressed_msg);
                        }
#else
                        throw(std::runtime_error("Program compiled without USE_COMPRESSION. Cannot read compressed message"));
#endif
                    }
                }
            }
        }
    }

    void BaseClient::ProcessPacket(const std::vector<unsigned char> &packet)
    {
        if (packet.empty())
        {
            return;
        }

        std::vector<unsigned char>::const_iterator packet_iterator = packet.begin();
        size_t length = packet.size();

        int packet_id = ReadVarInt(packet_iterator, length);

        std::shared_ptr<Message> msg = MessageFactory::CreateMessage(packet_id, (int)state);

        if (packet_id < printed_packets.size() && printed_packets[packet_id])
        {
            std::cout << "Packet with id " << packet_id << " received. (Thread " << std::this_thread::get_id() << ")" << std::endl;
        }

        if (msg)
        {
            msg->Read(packet_iterator, length);
            msg->Dispatch(this);
        }

        if (packet_id < printed_packets.size() && printed_packets[packet_id])
        {
            std::cout << "Packet with id " << packet_id << " processed. (Thread " << std::this_thread::get_id() << ")" << std::endl;
        }
    }

    void BaseClient::RunSyncPos()
    {
        // Wait for 500 milliseconds before starting to send position continuously
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        auto last_send = std::chrono::system_clock::now();
        std::shared_ptr<PlayerPositionAndLookServerbound> msg_position(new PlayerPositionAndLookServerbound);
        bool has_moved = false;

        while (state == State::Play)
        {
            // End of the current tick
            auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(50);

            if (player && player->GetPosition().y < 1000.0)
            {
                if (afk_only)
                {
                    has_moved = false;
                }
                else
                {
                    std::lock_guard<std::mutex> player_guard(player_mutex);
                    //Check that we did not go through a block
                    Physics();

                    if (std::abs(player->GetSpeed().x) > 1e-3 ||
                        std::abs(player->GetSpeed().y) > 1e-3 ||
                        std::abs(player->GetSpeed().z) > 1e-3)
                    {
                        has_moved = true;
                    }
                    else
                    {
                        has_moved = false;
                    }

                    //Avoid forever falling if position is <= 0.0
                    if (player->GetPosition().y <= 0.0)
                    {
                        player->SetY(0.0);
                        player->SetSpeedY(0.0);
                        player->SetOnGround(true);
                    }

                    // Reset the speed until next frame
                    // Update the gravity value if needed
                    player->SetSpeedX(0.0);
                    player->SetSpeedZ(0.0);
                    if (player->GetOnGround())
                    {
                        player->SetSpeedY(0.0);
                    }
                    else
                    {
                        player->SetSpeedY((player->GetSpeed().y - 0.08) * 0.98);//TODO replace hardcoded value?
                    }
                }

#if USE_GUI
                if (has_moved)
                {
                    renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62, player->GetPosition().z, player->GetYaw(), player->GetPitch());
                }
#endif
                msg_position->SetX(player->GetPosition().x);
                msg_position->SetFeetY(player->GetPosition().y);
                msg_position->SetZ(player->GetPosition().z);
                msg_position->SetYaw(player->GetYaw());
                msg_position->SetPitch(player->GetPitch());
                msg_position->SetOnGround(player->GetOnGround());

                if (has_moved || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_send).count() >= 1000)
                {
                    Send(msg_position);
                    last_send = std::chrono::system_clock::now();
                }
            }
            std::this_thread::sleep_until(end);
        }
    }

    void BaseClient::Physics()
    {
        //If the player did not move we assume it does not collide
        if (abs(player->GetSpeed().x) < 1e-3 && 
            abs(player->GetSpeed().y) < 1e-3 && 
            abs(player->GetSpeed().z) < 1e-3)
        {
            return;
        }

        Vector3<double> min_player_collider, max_player_collider;
        
        for (int i = 0; i < 3; ++i)
        {
            min_player_collider[i] = std::min(player->GetCollider().GetMin()[i], player->GetCollider().GetMin()[i] + player->GetSpeed()[i]);
            max_player_collider[i] = std::max(player->GetCollider().GetMax()[i], player->GetCollider().GetMax()[i] + player->GetSpeed()[i]);
        }

        AABB broadphase_collider = AABB((min_player_collider + max_player_collider) / 2.0, (max_player_collider - min_player_collider) / 2.0);

        bool has_hit_down = false;
        bool has_hit_up = false;
        
        Position cube_pos;
        for (int x = (int)std::floor(min_player_collider.x); x < (int)std::ceil(max_player_collider.x); ++x)
        {
            cube_pos.x = x;
            for (int y = (int)std::floor(min_player_collider.y); y < (int)std::ceil(max_player_collider.y); ++y)
            {
                cube_pos.y = y;
                for (int z = (int)std::floor(min_player_collider.z); z < (int)std::ceil(max_player_collider.z); ++z)
                {
                    cube_pos.z = z;

                    Block block;
                    {
                        std::lock_guard<std::mutex> mutex_guard(world_mutex);
                        const Block *block_ptr = world->GetBlock(cube_pos);

                        if (block_ptr == nullptr)
                        {
                            continue;
                        }
                        block = *block_ptr;
                    }

                    if (!block.GetBlockstate()->IsSolid())
                    {
                        continue;
                    }

                    const std::vector<AABB> &block_colliders = block.GetBlockstate()->GetModel(block.GetModelId()).GetColliders();

                    for (int i = 0; i < block_colliders.size(); ++i)
                    {
                        if (!broadphase_collider.Collide(block_colliders[i] + Vector3<double>(cube_pos.x, cube_pos.y, cube_pos.z)))
                        {
                            continue;
                        }

                        Vector3<double> normal;
                        const double speed_fraction = player->GetCollider().SweptCollide(player->GetSpeed(), block_colliders[i] + Vector3<double>(cube_pos.x, cube_pos.y, cube_pos.z), normal);

                        if (speed_fraction < 1.0)
                        {
                            const Vector3<double> remaining_speed = player->GetSpeed() * (1.0 - speed_fraction);

                            // We remove epsilon to be sure we do not go
                            // through the face due to numerical imprecision
                            player->SetSpeed(player->GetSpeed() * (speed_fraction - 1e-6) + // Base speed truncated
                                (remaining_speed - normal * remaining_speed.dot(normal))); // Remaining speed projected on the plane
                        }

                        if (normal.y == 1.0)
                        {
                            has_hit_down = true;
                        }
                        else if (normal.y == -1.0)
                        {
                            has_hit_up = true;
                        }

                    }
                }
            }
        }
        player->SetPosition(player->GetPosition() + player->GetSpeed());
        player->SetOnGround(has_hit_down);
        if (has_hit_up)
        {
            player->SetSpeedY(0.0);
        }
    }

    void BaseClient::Disconnect()
    {
        state = State::None;
        game_mode = GameMode::None;
        dimension = Dimension::None;
        difficulty = Difficulty::None;
#if PROTOCOL_VERSION > 463
        difficulty_locked = true;
#endif
        is_hardcore = false;
        compression = -1;

        if (com)
        {
            com->close();
        }

        process_condition.notify_all();

        if (m_thread_process.joinable())
        {
            m_thread_process.join();
        }

#if USE_GUI
        condition_rendering.notify_all();
        if (m_thread_update_renderer.joinable())
        {
            m_thread_update_renderer.join();
        }

        if (renderer)
        {
            renderer->Close();
        }
#endif

        if (m_thread_physics.joinable())
        {
            m_thread_physics.join();
        }

        com.reset();
        world.reset();
        inventory_manager.reset();
        player.reset();
#if USE_GUI
        renderer.reset();
#endif
    }

    void BaseClient::OnNewPacket(const std::vector<unsigned char> &packet)
    {
        std::unique_lock<std::mutex> lck(mutex_process);
        packets_to_process.push_back(packet);
        process_condition.notify_all();
    }

#ifdef USE_GUI

    void BaseClient::AddChunkToUpdate(const int x, const int z)
    {
        const std::vector<Position> chunk_pos = { {Position(x, 0, z), Position(x - 1, 0, z),
                    Position(x + 1, 0 , z), Position(x, 0, z - 1), Position(x, 0, z + 1)} };

        std::lock_guard<std::mutex> guard_rendering(mutex_rendering);
        for (int i = 0; i < chunk_pos.size(); ++i)
        {
            chunks_to_render.insert(chunk_pos[i]);
        }
        condition_rendering.notify_all();
    }

    void BaseClient::WaitForRenderingUpdate()
    {
        while (state == State::Play)
        {
            {
                std::unique_lock<std::mutex> lck(mutex_rendering);
                condition_rendering.wait(lck);
            }

            while (!chunks_to_render.empty())
            {
                Position pos;
                mutex_rendering.lock();
                if (!chunks_to_render.empty())
                {
                    auto posIterator = chunks_to_render.begin();
                    pos = *posIterator;
                    chunks_to_render.erase(posIterator);
                }
                mutex_rendering.unlock();

                std::shared_ptr<const Chunk> chunk;
                // Get the new values in the world
                world_mutex.lock();
                bool has_chunk_been_modified = world->HasChunkBeenModified(pos.x, pos.z);
                if (has_chunk_been_modified)
                {
                    chunk = world->GetChunkCopy(pos.x, pos.z);
                    world->ResetChunkModificationState(pos.x, pos.z);
                }
                world_mutex.unlock();

                if (has_chunk_been_modified)
                {
                    renderer->UpdateChunk(pos.x, pos.z, chunk);
                    renderer->UpdateBuffer();
                }

                // If we left the game, we don't need to process 
                // the rest of the data, just discard them
                if (state != State::Play)
                {
                    chunks_to_render.clear();
                    break;
                }
            }
        }
    }
#endif

    void BaseClient::Handle(Message &msg)
    {

    }

    void BaseClient::Handle(DisconnectLogin &msg)
    {
        std::cout << msg.GetReason().GetText() << std::endl;
        std::cout << "Disconnecting ..." << std::endl;

        Disconnect();
    }

    void BaseClient::Handle(LoginSuccess &msg)
    {
        state = State::Play;

        if (!player)
        {
            player = std::shared_ptr<Player>(new Player);
        }
        if (!world)
        {
            world = std::shared_ptr<World>(new World);
        }
        if (!inventory_manager)
        {
            inventory_manager = std::shared_ptr<InventoryManager>(new InventoryManager);
        }

#if USE_GUI
        renderer = std::shared_ptr<Renderer::CubeWorldRenderer>(new Renderer::CubeWorldRenderer(800, 600, AssetsManager::getInstance().GetTexturesPathsNames(), CHUNK_WIDTH, false));

        // Launche the updating rendering thread
        m_thread_update_renderer = std::thread(&BaseClient::WaitForRenderingUpdate, this);
#endif
        
        // Launch the physics thread (continuously sending the position to the server)
        m_thread_physics = std::thread(&BaseClient::RunSyncPos, this);
    }

    void BaseClient::Handle(SetCompression &msg)
    {
        compression = msg.GetThreshold();
    }

    void BaseClient::Handle(BlockChange &msg)
    {
#if PROTOCOL_VERSION < 347
        unsigned int id;
        unsigned char metadata; 
#endif
        
        { // Scope for lock_guard
            std::lock_guard<std::mutex> world_guard(world_mutex);
#if PROTOCOL_VERSION < 347
            Blockstate::IdToIdMetadata(msg.GetBlockId(), id, metadata);
            world->SetBlock(msg.GetLocation(), id, metadata);
#else
            world->SetBlock(msg.GetLocation(), msg.GetBlockId());
#endif
        }

#ifdef USE_GUI
        Position chunk_coords = Chunk::BlockCoordsToChunkCoords(msg.GetLocation());
        AddChunkToUpdate(chunk_coords.x, chunk_coords.z);
#endif
    }

    void BaseClient::Handle(ServerDifficulty &msg)
    {
        difficulty = msg.GetDifficulty();
#if PROTOCOL_VERSION > 463
        difficulty_locked = msg.GetDifficultyLocked();
#endif
    }

    void BaseClient::Handle(MultiBlockChange &msg)
    {
        { // Scope for lock guard
            std::lock_guard<std::mutex> world_guard(world_mutex);
            for (int i = 0; i < msg.GetRecordCount(); ++i)
            {
                unsigned char x = (msg.GetRecords()[i].GetHorizontalPosition() >> 4) & 0x0F;
                unsigned char z = msg.GetRecords()[i].GetHorizontalPosition() & 0x0F;

                Position cube_pos(CHUNK_WIDTH * msg.GetChunkX() + x, msg.GetRecords()[i].GetYCoordinate(), CHUNK_WIDTH * msg.GetChunkZ() + z);
                
#if PROTOCOL_VERSION < 347
                unsigned int id;
                unsigned char metadata;
                Blockstate::IdToIdMetadata(msg.GetRecords()[i].GetBlockId(), id, metadata);

                world->SetBlock(cube_pos, id, metadata);
#else
                world->SetBlock(cube_pos, msg.GetRecords()[i].GetBlockId());
#endif
            }
        }
#ifdef USE_GUI
        AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
#endif // USE_GUI
    }

    void BaseClient::Handle(ConfirmTransactionClientbound &msg)
    {
        //If the transaction was not accepted, we must apologize
        if (!msg.GetAccepted())
        {
            std::shared_ptr<ConfirmTransactionServerbound> apologize_msg(new ConfirmTransactionServerbound);
            apologize_msg->SetWindowId(msg.GetWindowId());
            apologize_msg->SetActionNumber(msg.GetActionNumber());
            apologize_msg->SetAccepted(msg.GetAccepted());

            Send(apologize_msg);
        }
        else
        {
            // TODO if accepted
        }
    }

    void BaseClient::Handle(DisconnectPlay &msg)
    {
        std::cout << msg.GetReason().GetText() << std::endl;
        std::cout << "Disconnecting ..." << std::endl;
        Disconnect();
    }

    void BaseClient::Handle(UnloadChunk &msg)
    {
        { // Scope for lock_guard
            std::lock_guard<std::mutex> world_guard(world_mutex);
            world->RemoveChunk(msg.GetChunkX(), msg.GetChunkZ());
        }
#if USE_GUI
        AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
#endif
    }

    void BaseClient::Handle(KeepAliveClientbound &msg)
    {
        std::shared_ptr<KeepAliveServerbound> keep_alive_msg(new KeepAliveServerbound);
        keep_alive_msg->SetKeepAliveId(msg.GetKeepAliveId());
        Send(keep_alive_msg);
    }

    void BaseClient::Handle(ChunkData &msg)
    {
        if (afk_only)
        {
            return;
        }

        Dimension chunk_dim;
        {
            std::lock_guard<std::mutex> world_guard(world_mutex);
            chunk_dim = world->GetDimension(msg.GetChunkX(), msg.GetChunkZ());
        }

        if (msg.GetGroundUpContinuous())
        {
            bool success = true;
            if (chunk_dim != dimension)
            {
                std::lock_guard<std::mutex> world_guard(world_mutex);
                success = world->AddChunk(msg.GetChunkX(), msg.GetChunkZ(), dimension);
            }

            if (!success)
            {
                std::cerr << "Error adding chunk in pos : " << msg.GetChunkX() << ", " << msg.GetChunkZ() << " in dimension " << (int)dimension << std::endl;
                return;
            }
        }

        { // lock guard scope
            std::lock_guard<std::mutex> world_guard(world_mutex);
            world->LoadDataInChunk(msg.GetChunkX(), msg.GetChunkZ(), msg.GetData(), msg.GetPrimaryBitMask(), msg.GetGroundUpContinuous());
            world->LoadBlockEntityDataInChunk(msg.GetChunkX(), msg.GetChunkZ(), msg.GetBlockEntitiesData(), msg.GetNumberBlockEntities());
        }

        //Update GUI
#ifdef USE_GUI
        AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
#endif //USE_GUI
    }

    void BaseClient::Handle(JoinGame &msg)
    {
        player_mutex.lock();
        player->SetEID(msg.GetEntityId());
        player_mutex.unlock();
        game_mode = (GameMode)(msg.GetGamemode() & 0x03);
        is_hardcore = msg.GetGamemode() & 0x08;

        dimension = msg.GetDimension();

#if PROTOCOL_VERSION < 464
        difficulty = msg.GetDifficulty();
#endif
    }

    void BaseClient::Handle(Entity &msg)
    {
        std::cout << "New entity created with ID: " << msg.GetEntityId() << std::endl;
        //TODO add the entity to the world
    }

    void BaseClient::Handle(EntityRelativeMove &msg)
    {
        std::lock_guard<std::mutex> player_guard(player_mutex);
        if (msg.GetEntityId() == player->GetEID())
        {
            player->SetX((msg.GetDeltaX() / 128.0f + player->GetPosition().x * 32.0f) / 32.0f);
            player->SetY((msg.GetDeltaY() / 128.0f + player->GetPosition().y * 32.0f) / 32.0f);
            player->SetZ((msg.GetDeltaZ() / 128.0f + player->GetPosition().z * 32.0f) / 32.0f);
            player->SetOnGround(msg.GetOnGround());

#ifdef USE_GUI
            renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
#endif // USE_GUI
        }
        else
        {
            //TODO Change entity's position in the world
        }
    }

    void BaseClient::Handle(EntityLookAndRelativeMove &msg)
    {
        std::lock_guard<std::mutex> player_guard(player_mutex);
        if (msg.GetEntityId() == player->GetEID())
        {
            player->SetX((msg.GetDeltaX() / 128.0f + player->GetPosition().x * 32.0f) / 32.0f);
            player->SetY((msg.GetDeltaY() / 128.0f + player->GetPosition().y * 32.0f) / 32.0f);
            player->SetZ((msg.GetDeltaZ() / 128.0f + player->GetPosition().z * 32.0f) / 32.0f);
            player->SetYaw(360.0f * msg.GetYaw() / 256.0f);
            player->SetPitch(360.0f * msg.GetPitch() / 256.0f);
            player->SetOnGround(msg.GetOnGround());

#ifdef USE_GUI
            renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
#endif // USE_GUI
        }
        else
        {
            //TODO Change entity's position and rotation in the world
        }
    }

    void BaseClient::Handle(EntityLook &msg)
    {
        std::lock_guard<std::mutex> player_guard(player_mutex);
        if (msg.GetEntityId() == player->GetEID())
        {
            player->SetYaw(360.0f * msg.GetYaw() / 256.0f);
            player->SetPitch(360.0f * msg.GetPitch() / 256.0f);
            player->SetOnGround(msg.GetOnGround());

#ifdef USE_GUI
            renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
#endif // USE_GUI
        }
        else
        {
            //TODO Change entity's rotation in the world
        }
    }

    void BaseClient::Handle(PlayerPositionAndLookClientbound &msg)
    {
        std::lock_guard<std::mutex> player_guard(player_mutex);
        (msg.GetFlags() & 0x01) ? player->SetX(player->GetPosition().x + msg.GetX()) : player->SetX(msg.GetX());
        (msg.GetFlags() & 0x02) ? player->SetY(player->GetPosition().y + msg.GetY()) : player->SetY(msg.GetY());
        (msg.GetFlags() & 0x04) ? player->SetZ(player->GetPosition().z + msg.GetZ()) : player->SetZ(msg.GetZ());
        (msg.GetFlags() & 0x08) ? player->SetYaw(player->GetYaw() + msg.GetYaw()) : player->SetYaw(msg.GetYaw());
        (msg.GetFlags() & 0x10) ? player->SetPitch(player->GetPitch() + msg.GetPitch()) : player->SetPitch(msg.GetPitch());

        std::shared_ptr<TeleportConfirm> confirm_msg(new TeleportConfirm);
        confirm_msg->SetTeleportId(msg.GetTeleportId());

        Send(confirm_msg);

#ifdef USE_GUI
        renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
#endif // USE_GUI
    }

    void BaseClient::Handle(UpdateHealth &msg)
    {
        player_mutex.lock();
        player->SetHealth(msg.GetHealth());
        player->SetFood(msg.GetFood());
        player->SetFoodSaturation(msg.GetFoodSaturation());
        player_mutex.unlock();

        if (msg.GetHealth() <= 0.0f && auto_respawn)
        {
            std::shared_ptr<ClientStatus> status_message(new ClientStatus);
            status_message->SetActionID(0);
            Send(status_message);
        }
    }

    void BaseClient::Handle(EntityTeleport &msg)
    {
        std::lock_guard<std::mutex> player_guard(player_mutex);
        if (msg.GetEntityId() == player->GetEID())
        {
            player->SetX(msg.GetX());
            player->SetY(msg.GetY());
            player->SetZ(msg.GetZ());
            player->SetYaw(360.0f * msg.GetYaw() / 256.0f);
            player->SetPitch(360.0f * msg.GetPitch() / 256.0f);
            player->SetOnGround(msg.GetOnGround());

#ifdef USE_GUI
            renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
#endif // USE_GUI
        }
        else
        {
            //TODO Change entity's position and rotation in the world
        }
    }

    void BaseClient::Handle(PlayerAbilitiesClientbound &msg)
    {
        player_mutex.lock();
        player->SetIsInvulnerable(msg.GetFlags() & 0x01);
        player->SetIsFlying(msg.GetFlags() & 0x02);
        allow_flying = msg.GetFlags() & 0x04;
        creative_mode = msg.GetFlags() & 0x08;

        player->SetFlyingSpeed(msg.GetFlyingSpeed());
        player_mutex.unlock();

        //TODO do something with the field of view modifier


        std::shared_ptr<ClientSettings> settings_msg(new ClientSettings);
        settings_msg->SetLocale("fr_FR");
        settings_msg->SetViewDistance(10);
        settings_msg->SetChatMode(ChatMode::Enabled);
        settings_msg->SetChatColors(true);
        settings_msg->SetDisplayedSkinParts(0xFF);
        settings_msg->SetMainHand(Hand::Right);

        Send(settings_msg);
    }

    void BaseClient::Handle(TimeUpdate &msg)
    {
#ifdef USE_GUI
        renderer->SetDayTime(((msg.GetTimeOfDay() + 6000) % 24000) / 24000.0f);
#endif
    }

    void BaseClient::Handle(EncryptionRequest &msg)
    {
        if (authentifier == nullptr)
        {
            std::cerr << "Error, authentication asked while no password has been provided, make sure to connect with a valid Mojang Account" << std::endl;
            Disconnect();
            return;
        }

#ifdef USE_ENCRYPTION
        std::shared_ptr<AESEncrypter> encrypter = std::shared_ptr<AESEncrypter>(new AESEncrypter());

        std::vector<unsigned char> encrypted_token;
        std::vector<unsigned char> encrypted_shared_secret;
        std::vector<unsigned char> raw_shared_secret;

        encrypter->Init(msg.GetPublicKey(), msg.GetVerifyToken(),
            raw_shared_secret, encrypted_token, encrypted_shared_secret);

        authentifier->JoinServer(msg.GetServerID(), raw_shared_secret, msg.GetPublicKey());

        std::shared_ptr<EncryptionResponse> response_msg(new EncryptionResponse);
        response_msg->SetSharedSecret(encrypted_shared_secret);
        response_msg->SetVerifyToken(encrypted_token);

        Send(response_msg);
        
        // Enable encryption for now on
        com->SetEncrypter(encrypter);
#else
        throw(std::runtime_error("Your version of botcraft doesn't support encryption. Either run your server with online-mode=false or recompile botcraft"));
#endif
    }

    void BaseClient::Handle(Respawn &msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);
        // Clear all current chunks
        const auto& chunks = world->GetAllChunks();
        std::vector<std::pair<int, int> > chunks_to_remove;
        chunks_to_remove.reserve(chunks.size());
        for (auto it = chunks.begin(); it != chunks.end(); ++it)
        {
            chunks_to_remove.push_back(it->first);
        }

        for (int i = 0; i < chunks_to_remove.size(); ++i)
        {
            world->RemoveChunk(chunks_to_remove[i].first, chunks_to_remove[i].second);
#ifdef USE_GUI
            AddChunkToUpdate(chunks_to_remove[i].first, chunks_to_remove[i].second);
#endif
        }

        dimension = msg.GetDimension();
#if PROTOCOL_VERSION < 464
        difficulty = msg.GetDifficulty();
#endif
        game_mode = msg.GetGamemode();
    }

#if PROTOCOL_VERSION > 404
    void BaseClient::Handle(UpdateLight &msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);
        world->UpdateChunkLight(msg.GetChunkX(), msg.GetChunkZ(), dimension,
            msg.GetSkyLightMask(), msg.GetEmptySkyLightMask(), msg.GetSkyLightArrays(), true);
        world->UpdateChunkLight(msg.GetChunkX(), msg.GetChunkZ(), dimension,
            msg.GetBlockLightMask(), msg.GetEmptyBlockLightMask(), msg.GetBlockLightArrays(), false);
    }
#endif

    void BaseClient::Handle(UpdateBlockEntity &msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);
        world->SetBlockEntityData(msg.GetLocation(), msg.GetNBTData());
    }

    void BaseClient::Handle(PlayerInfo &msg)
    {

    }

    void BaseClient::Handle(SetSlot &msg)
    {
        {
            std::lock_guard<std::mutex> inventories_locker(inventory_manager_mutex);
        
            if (msg.GetWindowId() == -1 && msg.GetSlot() == -1)
            {
                inventory_manager->SetCursor(msg.GetSlotData());
            }
            else if (msg.GetWindowId() == -2)
            {
                inventory_manager->SetSlot(Inventory::PLAYER_INVENTORY_INDEX, msg.GetSlot(), msg.GetSlotData());
            }
            else if (msg.GetWindowId() >= 0)
            {
                inventory_manager->SetSlot(msg.GetWindowId(), msg.GetSlot(), msg.GetSlotData());
            }
            else
            {
                std::cerr << "Warning, unknown window called in SetSlot: " << msg.GetWindowId() << ", " << msg.GetSlot() << std::endl;
            }
        }
    }

    void BaseClient::Handle(WindowItems &msg)
    {
        {
            std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);

            for (int i = 0; i < msg.GetCount(); ++i)
            {
                inventory_manager->SetSlot(msg.GetWindowId(), i, msg.GetSlotData()[i]);
            }
        }
    }

    void BaseClient::Handle(OpenWindow &msg)
    {
        {
            std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);

            inventory_manager->AddInventory(msg.GetWindowId());
        }
    }

    void BaseClient::Handle(HeldItemChangeClientbound &msg)
    {
        {
            std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
            inventory_manager->SetHotbarSelected(msg.GetSlot());
        }
    }


} //Botcraft