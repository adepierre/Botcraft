#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>
#include <botcraft/Game/Inventory/Window.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/AI/Tasks/AllTasks.hpp>
#include <botcraft/Utilities/NBTUtilities.hpp>
#include <botcraft/Utilities/MiscUtilities.hpp>

#include <queue>

#include "WorldEaterTasks.hpp"
#include "WorldEaterUtilities.hpp"

using namespace Botcraft;

enum class ActionType
{
    BreakBlock,
    BreakPillar,
    PlaceSolidBlock,
    FillFluidBlock,
    PlacePillarBlock,
    PlaceTempBlock,
    PlaceLadderBlock
};


Status Init(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    const int bot_index = blackboard.Get<int>("Eater.bot_index");
    const int num_bot = blackboard.Get<int>("Eater.num_bot");
    const Position start_block = blackboard.Get<Position>("Eater.start_block");
    const Position end_block = blackboard.Get<Position>("Eater.end_block");

    // Get initial bot position
    Position init_pos;
    std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        init_pos = Position(
            static_cast<int>(std::floor(local_player->GetX())),
            static_cast<int>(std::floor(local_player->GetY())),
            static_cast<int>(std::floor(local_player->GetZ()))
        );
    }
    blackboard.Set<Position>("Eater.init_pos", init_pos);

    const Position min_block(
        std::min(start_block.x, end_block.x),
        std::min(start_block.y, end_block.y),
        std::min(start_block.z, end_block.z)
    );
    const Position max_block(
        std::max(start_block.x, end_block.x),
        std::max(start_block.y, end_block.y),
        std::max(start_block.z, end_block.z)
    );

    // Find out on which axis we "cut" the work area for all the bots
    // If the bot is in a corner, one of the two sides will be chosen
    Direction input_edge;
    if (init_pos.x < min_block.x)
    {
        input_edge = Direction::West;
    }
    else if (init_pos.x > max_block.x)
    {
        input_edge = Direction::East;
    }
    else if (init_pos.z < min_block.z)
    {
        input_edge = Direction::North;
    }
    else if (init_pos.z > max_block.z)
    {
        input_edge = Direction::South;
    }
    else
    {
        LOG_ERROR("Bot is inside the working area, please move it before starting");
        return Status::Failure;
    }
    blackboard.Set<Direction>("Eater.input_edge", input_edge);

    std::shared_ptr<World> world = client.GetWorld();

    Position this_bot_start;
    Position this_bot_end;
    Position ladder_pillar_position;
    Position ladder_position;
    PlayerDiggingFace ladder_face;
    if (input_edge == Direction::West || input_edge == Direction::East)
    {
        const float bot_area_size = static_cast<float>(max_block.z - min_block.z + 1) / num_bot;
        this_bot_start = Position(
            min_block.x,
            std::min(max_block.y, world->GetMinY() + world->GetHeight()),
            static_cast<int>(std::floor(min_block.z + bot_area_size * bot_index))
        );
        this_bot_end = Position(
            max_block.x,
            std::max(min_block.y, world->GetMinY()),
            (bot_index == num_bot - 1) ? max_block.z : static_cast<int>(std::floor(min_block.z + bot_area_size * bot_index + bot_area_size - 1))
        );
        ladder_pillar_position.x = input_edge == Direction::West ? min_block.x - 2 : max_block.x + 2;
        ladder_pillar_position.z = (this_bot_end.z + this_bot_start.z) / 2;
        ladder_position.x = input_edge == Direction::West ? min_block.x - 1 : max_block.x + 1;
        ladder_position.z = (this_bot_end.z + this_bot_start.z) / 2;
        ladder_face = input_edge == Direction::West ? Direction::East : Direction::West;
    }
    else
    {
        const float bot_area_size = static_cast<float>(max_block.x - min_block.x + 1) / num_bot;
        this_bot_start = Position(
            static_cast<int>(std::floor(min_block.x + bot_area_size * bot_index)),
            max_block.y,
            min_block.z
        );
        this_bot_end = Position(
            (bot_index == num_bot - 1) ? max_block.x : static_cast<int>(std::floor(min_block.x + bot_area_size * bot_index + bot_area_size - 1)),
            min_block.y,
            max_block.z
        );
        ladder_pillar_position.x = (this_bot_end.x + this_bot_start.x) / 2;
        ladder_pillar_position.z = input_edge == Direction::North ? min_block.z - 2 : max_block.z + 2;
        ladder_position.x = (this_bot_end.x + this_bot_start.x) / 2;
        ladder_position.z = input_edge == Direction::North ? min_block.z - 1 : max_block.z + 1;
        ladder_face = input_edge == Direction::North ? Direction::South : Direction::North;
    }

    {
        std::lock_guard<std::mutex> lock(world->GetMutex());
        // Get top of ladder pillar (first solid block going downard
        // from the top of the working area)
        Position block_pos = ladder_pillar_position;
        for (int y = this_bot_start.y; y >= world->GetMinY(); --y)
        {
            block_pos.y = y;
            const Block* block = world->GetBlock(block_pos);
            if (block && block->GetBlockstate()->IsSolid())
            {
                ladder_pillar_position.y = y;
                ladder_position.y = y;
                break;
            }
        }

        // Check the whole area is loaded (required for the planning algorithm to work properly)
        if (!world->IsLoaded(this_bot_end) || !world->IsLoaded(this_bot_start))
        {
            LOG_ERROR("Work area of " << client.GetNetworkManager()->GetMyName() << " (from " << this_bot_start << "to " << this_bot_end << ") is not fully loaded, please move it closer before launching it");
            return Status::Failure;
        }
    }

    blackboard.Set<Position>("Eater.start_block", this_bot_start);
    blackboard.Set<Position>("Eater.end_block", this_bot_end);
    blackboard.Set<Position>("Eater.ladder_pillar", ladder_pillar_position);
    blackboard.Set<Position>("Eater.ladder", ladder_position);
    blackboard.Set<PlayerDiggingFace>("Eater.ladder_face", ladder_face);
    blackboard.Set<int>("Eater.current_layer", this_bot_start.y);
    blackboard.Set<bool>("Eater.init", true);
    blackboard.Set<std::array<ToolType, 5>>("Eater.tools", {
        ToolType::Axe,
        ToolType::Hoe,
        ToolType::Pickaxe,
        ToolType::Shears,
        ToolType::Shovel
    });

    // Get a set for spared/collected blocks/items
    blackboard.Set<std::unordered_set<std::string>>("Eater.spared_blocks", SplitString(blackboard.Get<std::string>("Eater.spared_blocks"), ','));
    std::unordered_set<ItemId> collected_blocks;
    for (const auto& s : SplitString(blackboard.Get<std::string>("Eater.collected_blocks"), ','))
    {
        collected_blocks.insert(AssetsManager::getInstance().GetItemID(s));
    }
    blackboard.Set<std::unordered_set<ItemId>>("Eater.collected_blocks", collected_blocks);


    if (!IdentifyBaseCampLayout(client))
    {
        return Status::Failure;
    }

    // Check the whole area for spawner/shrieker and log them to user
    if (bot_index == 0)
    {
        std::lock_guard<std::mutex> lock(world->GetMutex());
        Position current_position;
        for (int y = min_block.y - 16; y <= max_block.y + 16; ++y)
        {
            current_position.y = y;
            for (int x = min_block.x - 16; x <= max_block.x + 16; ++x)
            {
                current_position.x = x;
                for (int z = min_block.z - 16; z <= max_block.z + 16; ++z)
                {
                    current_position.z = z;
                    const Block* block = world->GetBlock(current_position);
                    if (block != nullptr && !block->GetBlockstate()->IsAir())
                    {
                        if (block->GetBlockstate()->GetName() == "minecraft:spawner")
                        {
                            LOG_WARNING("Spawner detected at " << current_position << ". Please make sure it's spawnproofed as I don't like to die (it tickles)");
                        }
#if PROTOCOL_VERSION > 758
                        else if (block->GetBlockstate()->GetName() == "minecraft:sculk_shrieker")
                        {
                            LOG_WARNING("Shrieker detected at " << current_position << ". Please make sure it won't spawn a warden. They hit hard.");
                        }
#endif
                    }
                }
            }
        }
    }

    return Status::Success;
}

Status GetNextAction(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    const std::queue<std::pair<Position, ActionType>>& queue = blackboard.Get<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue");

    if (queue.empty())
    {
        return Status::Failure;
    }

    blackboard.Set<std::pair<Position, ActionType>>("Eater.next_action", queue.front());

    return Status::Success;
}

Status ExecuteAction(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();
    std::shared_ptr<World> world = client.GetWorld();
    std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
    std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
    const std::unordered_set<std::string>& spared_blocks = blackboard.Get<std::unordered_set<std::string>>("Eater.spared_blocks");
    const Position& start_block = blackboard.Get<Position>("Eater.start_block");
    const Position& end_block = blackboard.Get<Position>("Eater.end_block");
    const std::pair<Position, ActionType>& action = blackboard.Get<std::pair<Position, ActionType>>("Eater.next_action");

    Vector3<double> player_position;
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        player_position = local_player->GetPosition();
    }
    const Position player_block_position(
        static_cast<int>(std::floor(player_position.x)),
        static_cast<int>(std::floor(player_position.y)),
        static_cast<int>(std::floor(player_position.z))
    );
    const double squared_dist_to_action = local_player->GetPosition().SqrDist(action.first);

    // Stop sprinting when exiting this function (in case we don't sprint, it's a no-op)
    Utilities::OnEndScope stop_sprinting([&]() { StopSprinting(client); });

    // Start sprinting if we need to move more than 10 blocks
    if (squared_dist_to_action > 10.0 * 10.0)
    {
        StartSprinting(client);
    }

    const Blockstate* blockstate = nullptr;
    // Get this position blockstate
    {
        std::lock_guard<std::mutex> lock(world->GetMutex());
        const Block* block = world->GetBlock(action.first);
        if (block != nullptr)
        {
            blockstate = block->GetBlockstate();
        }
    }

    // If we need to spare this block or if it's one we can't break anyway
    if (blockstate != nullptr &&
        (spared_blocks.find(blockstate->GetName()) != spared_blocks.cend() ||
        (!blockstate->IsAir() && !blockstate->IsFluid() && blockstate->GetHardness() < 0)))
    {
        return Status::Success;
    }

    const std::string block_to_place =
        action.second == ActionType::PlaceLadderBlock ?
        "minecraft:ladder" :
        blackboard.Get<std::string>("Eater.temp_block");

    // Break block if that's the action, or if we need to place a block that's not the one currently there
    if (blockstate != nullptr && !blockstate->IsAir() && !blockstate->IsFluid() &&
        (action.second == ActionType::BreakBlock ||
            action.second == ActionType::BreakPillar ||
            (action.second == ActionType::FillFluidBlock && blockstate->IsWaterlogged()) ||
            (action.second == ActionType::PlaceSolidBlock && (!blockstate->IsSolid() || (!blockstate->IsFluid() && blockstate->IsHazardous()) || CouldFallIfUpdated(blockstate->GetName()))) ||
            (action.second != ActionType::PlaceSolidBlock && action.second != ActionType::FillFluidBlock && blockstate->GetName() != block_to_place)))
    {
        // Check which tool type is the best
        const std::array<ToolType, 5>& tool_types = blackboard.Get<std::array<ToolType, 5>>("Eater.tools");
        ToolType best_tool_type = ToolType::None;
        float min_mining_time = std::numeric_limits<float>::max();

        for (const ToolType t : tool_types)
        {
            const float mining_time = blockstate->GetMiningTimeSeconds(t, static_cast<ToolMaterial>(static_cast<int>(ToolMaterial::NUM_TOOL_MATERIAL) - 1));
            if (mining_time < min_mining_time)
            {
                min_mining_time = mining_time;
                best_tool_type = t;
            }
        }

        // Set the best tool in hand
        std::string tool_name = "";
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            const std::map<short, ProtocolCraft::Slot>& inventory_slots = inventory_manager->GetPlayerInventory()->GetSlots();
            for (const auto& [i, slot] : inventory_slots)
            {
                if (i < Window::INVENTORY_STORAGE_START || i > Window::INVENTORY_OFFHAND_INDEX || slot.IsEmptySlot())
                {
                    continue;
                }

                const Item* item = AssetsManager::getInstance().GetItem(slot.GetItemID());
                if (item->GetToolType() == best_tool_type)
                {
                    // Check the tool won't break, with a "large" margin of 5 to be safe
                    const int damage_count = Utilities::GetDamageCount(slot.GetNBT());
                    if (damage_count < item->GetMaxDurability() - 6)
                    {
                        tool_name = item->GetName();
                        break;
                    }
                }
            }
        }

        // We don't have a tool of this type or it's too damaged
        if (tool_name == "")
        {
            return Status::Failure;
        }

        if (SetItemInHand(client, tool_name) == Status::Failure)
        {
            LOG_WARNING("Error trying to set " << tool_name << " in right hand");
            return Status::Failure;
        }

        Status goto_result = Status::Success;
        switch (action.second)
        {
        case ActionType::BreakBlock:
            // If we are standing on the current layer, we know we can break all blocks in range
            // as long as we are not standing on them. The ordering of the actions in the queue
            // gives us guarantees that we won't "break" the path back to the ladder as long as
            // we don't break the block under our feets
            if (player_position.y >= action.first.y + 1 && player_position.y < action.first.y + 2.5 &&
                player_block_position.x >= start_block.x && player_block_position.x <= end_block.x &&
                player_block_position.z >= start_block.z && player_block_position.z <= end_block.z)
            {
                goto_result = GoTo(client, action.first + Position(0, 1, 0), 4, 1, 1);
            }
            // Else, we should get back on top of the current layer first to be sure we won't
            // isolate us from the ladder access point
            else
            {
                goto_result = GoTo(client, action.first + Position(0, 1, 0));
                // If it succeeds, we are now on the current layer and can just find a spot to mine.
                if (goto_result == Status::Success)
                {
                    goto_result = GoTo(client, action.first + Position(0, 1, 0), 4, 1, 1);
                }
                // If it failed, try to find another close position as a backup plan.
                else
                {
                    for (int i = 1; i < 5; ++i)
                    {
                        goto_result = GoTo(client, action.first + Position(0, 1, 0), i, 1, 1);
                        if (goto_result == Status::Success)
                        {
                            break;
                        }
                    }
                }
            }
            break;
        case ActionType::BreakPillar:
            goto_result = GoTo(client, action.first + Position(0, 1, 0));
            break;
        default:
            break;
        }

        // Dig would call GoTo too, but without the min dist constraint we want
        if (goto_result == Status::Failure)
        {
            LOG_WARNING("Error trying to GoTo digging position " << action.first);
            return Status::Failure;
        }

        if (Dig(client, action.first, true, PlayerDiggingFace::Up) == Status::Failure)
        {
            LOG_WARNING("Error trying to Dig at " << action.first);
            return Status::Failure;
        }

        // After breaking a pillar, wait to land on the next pillar block
        if (action.second == ActionType::BreakPillar)
        {
            // Manually set on ground to false as the physics thread might not have yet registered the missing block
            {
                std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                local_player->SetOnGround(false);
            }
            auto start = std::chrono::steady_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 2000)
                {
                    LOG_WARNING("Timeout waiting to land after mining pillar block");
                    return Status::Failure;
                }
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    if (local_player->GetOnGround())
                    {
                        break;
                    }
                }
                client.Yield();
            }
        }
    }

    if ((action.second == ActionType::FillFluidBlock && blockstate != nullptr && (blockstate->IsFluid() || blockstate->IsWaterlogged() || blockstate->IsAir())) || // We need to place it if it's air as it could be part of a pathfinding requirements to go to next fluid block
        (action.second == ActionType::PlaceSolidBlock && (blockstate == nullptr || !blockstate->IsSolid() || blockstate->IsHazardous() || CouldFallIfUpdated(blockstate->GetName()))) ||
        ((action.second == ActionType::PlacePillarBlock || action.second == ActionType::PlaceTempBlock || action.second == ActionType::PlaceLadderBlock)
             && (blockstate == nullptr || blockstate->GetName() != block_to_place)))
    {
        if (HasItemInInventory(client, block_to_place, 1) == Status::Failure)
        {
            // If we don't have one item in inventory go back to basecamp to grab some
            return Status::Failure;
        }

        // PlaceBlock would call GoTo too, but without the min dist constraint we want
        Status goto_result = Status::Success;
        switch (action.second)
        {
        case ActionType::FillFluidBlock:
        case ActionType::PlaceSolidBlock:
        case ActionType::PlaceTempBlock:
            // If we are standing on the current layer
            if (player_position.y >= action.first.y + 1 && player_position.y < action.first.y + 2.5 &&
                player_block_position.x >= start_block.x && player_block_position.x <= end_block.x &&
                player_block_position.z >= start_block.z && player_block_position.z <= end_block.z)
            {
                goto_result = GoTo(client, action.first + Position(0, 1, 0), 3, 1, 1);
            }
            // Else, try to get back on the top layer fist
            else
            {
                goto_result = GoTo(client, action.first + Position(0, 1, 0), 1, 1, 1);
                // If it failed, try to find another close position as a backup plan.
                if (goto_result == Status::Failure)
                {
                    for (int i = 2; i < 5; ++i)
                    {
                        goto_result = GoTo(client, action.first + Position(0, 1, 0), i, 1, 1);
                        if (goto_result == Status::Success)
                        {
                            break;
                        }
                    }
                }
            }
            break;
        case ActionType::PlacePillarBlock:
        case ActionType::PlaceLadderBlock:
            goto_result = GoTo(client, action.first, 4, 2);
            break;
        default:
            break;
        }

        if (goto_result == Status::Failure)
        {
            LOG_WARNING("Error trying to GoTo digging position " << action.first);
            return Status::Failure;
        }

        if (PlaceBlock(client, block_to_place, action.first,
            action.second == ActionType::PlaceLadderBlock ?
                std::optional<PlayerDiggingFace>(blackboard.Get<PlayerDiggingFace>("Eater.ladder_face")) :
                std::nullopt, true, false) == Status::Failure)
        {
            // Retry, but this time with the cheaty midair placement
            if (PlaceBlock(client, block_to_place, action.first,
                action.second == ActionType::PlaceLadderBlock ?
                std::optional<PlayerDiggingFace>(blackboard.Get<PlayerDiggingFace>("Eater.ladder_face")) :
                PlayerDiggingFace::Up, true, true) == Status::Failure)
            {
                LOG_WARNING("Error trying to PlaceBlock (" << block_to_place << ") at " << action.first);
                return Status::Failure;
            }
        }
    }

    return Status::Success;
}

Status CheckActionsDone(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    const std::queue<std::pair<Position, ActionType>>& queue = blackboard.Get<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue");

    return queue.empty() ? Status::Success : Status::Failure;
}

Botcraft::Status ValidateCurrentLayer(Botcraft::SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();
    std::shared_ptr<World> world = client.GetWorld();

    const std::unordered_set<std::string>& spared_blocks = blackboard.Get<std::unordered_set<std::string>>("Eater.spared_blocks");
    const int current_layer = blackboard.Get<int>("Eater.current_layer");
    const Position& start_block = blackboard.Get<Position>("Eater.start_block");
    const Position& end_block = blackboard.Get<Position>("Eater.end_block");

    // Wait for the area to be loaded (in case a bot sharing the same world died as it unload the chunks for a brief moment)
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        // Something went wrong during waiting on ground
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 10000)
        {
            LOG_WARNING("Timeout waiting for chunk loading");
            return Status::Failure;
        }
        {
            std::lock_guard<std::mutex> lock(world->GetMutex());
            if (world->IsLoaded(start_block) && world->IsLoaded(end_block))
            {
                break;
            }
        }
        client.Yield();
    }

    // Check previous layers are indeed done
    {
        std::lock_guard<std::mutex> lock(world->GetMutex());
        Position current_position;
        for (int y = start_block.y; y > current_layer; --y)
        {
            current_position.y = y;
            for (int x = start_block.x; x <= end_block.x; ++x)
            {
                current_position.x = x;
                for (int z = start_block.z; z <= end_block.z; ++z)
                {
                    current_position.z = z;
                    const Block* block = world->GetBlock(current_position);
                    if (block != nullptr && !block->GetBlockstate()->IsAir() && spared_blocks.find(block->GetBlockstate()->GetName()) == spared_blocks.cend())
                    {
                        blackboard.Set<int>("Eater.current_layer", y);
                        return Status::Success;
                    }
                }
            }
        }
    }

    return Status::Success;
}

Status PopAction(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    NotifyOnEndUseRef<std::queue<std::pair<Position, ActionType>>> queue_ref = blackboard.GetRef<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue");
    std::queue<std::pair<Position, ActionType>>& queue = queue_ref.ref();

    if (queue.empty())
    {
        return Status::Failure;
    }

    queue.pop();

    return Status::Success;
}

Status IsInventoryFull(SimpleBehaviourClient& client)
{
    std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
    {
        std::lock_guard<std::mutex> lock_inventory(inventory_manager->GetMutex());
        std::shared_ptr<Window> player_inventory = inventory_manager->GetPlayerInventory();
        for (const auto& [idx, slot] : player_inventory->GetSlots())
        {
            if (idx < Window::INVENTORY_STORAGE_START || idx >= Window::INVENTORY_OFFHAND_INDEX)
            {
                continue;
            }
            if (slot.IsEmptySlot())
            {
                return Status::Failure;
            }
        }
    }
    return Status::Success;
}

Status CleanInventory(SimpleBehaviourClient& client)
{
    std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<World> world = client.GetWorld();
    std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();
    std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
    Blackboard& blackboard = client.GetBlackboard();
    const std::unordered_set<ItemId>& collected_items = blackboard.Get<std::unordered_set<ItemId>>("Eater.collected_blocks");

    if (HasItemInInventory(client, "minecraft:lava_bucket", 1) == Status::Failure)
    {
        // We are missing lava bucket, go back to basecamp to grab one
        return Status::Failure;
    }

    Vector3<double> init_position;
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }
    Position block_position(
        static_cast<int>(std::floor(init_position.x)),
        static_cast<int>(std::floor(init_position.y + 0.2)), // Add 0.2 in case we are on the top of an "almost full block" and don't want to place lava in our face :)
        static_cast<int>(std::floor(init_position.z))
    );

    bool on_fluid = false;
    {
        std::lock_guard<std::mutex> lock(world->GetMutex());
        const Block* block = world->GetBlock(block_position + Position(0, -1, 0));
        on_fluid = block != nullptr && (block->GetBlockstate()->IsFluid() || block->GetBlockstate()->IsWaterlogged());
    }

    // It's not a good idea to drop lava on top of a fluid, best case it's,
    // water and you'll get obsidian, worst case it's lava and you'll get
    // sadness and death
    if (on_fluid)
    {
        // Try to pathfind on top of previous position
        if (GoTo(client, blackboard.Get<std::pair<Position, ActionType>>("Eater.next_action").first + Position(0, 1, 0)) == Status::Failure)
        {
            // If it didn't work, the bot will go back to basecamp instead of wasting a bucket of lava
            return Status::Failure;
        }
    }

    LookAt(client, init_position, true);

    // Wait to be on ground
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        // Something went wrong during waiting on ground
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 2000)
        {
            LOG_WARNING("Timeout waiting for on ground trying to clean inventory");
            return Status::Failure;
        }
        {
            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
            if (local_player->GetOnGround())
            {
                break;
            }
        }
        client.Yield();
    }

     // Update positions in case we moved
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }
    block_position = Position(
        static_cast<int>(std::floor(init_position.x)),
        static_cast<int>(std::floor(init_position.y + 0.2)),
        static_cast<int>(std::floor(init_position.z))
    );

    // Items we don't want to throw in lava
    const std::unordered_set<ItemId> non_tool_items_to_keep = {
        AssetsManager::getInstance().GetItemID("minecraft:lava_bucket"),
        AssetsManager::getInstance().GetItemID("minecraft:golden_carrot"),
        AssetsManager::getInstance().GetItemID("minecraft:ladder"),
        AssetsManager::getInstance().GetItemID(blackboard.Get<std::string>("Eater.temp_block"))
    };
    std::vector<short> slots_to_throw;
    slots_to_throw.reserve(Window::INVENTORY_OFFHAND_INDEX);
    {
        std::lock_guard<std::mutex> lock_inventory(inventory_manager->GetMutex());
        std::shared_ptr<Window> player_inventory = inventory_manager->GetPlayerInventory();
        for (const auto& [idx, slot] : player_inventory->GetSlots())
        {
            // Don't throw lava bucket, food, temp block or tools
            if (idx < Window::INVENTORY_STORAGE_START ||
                slot.IsEmptySlot() ||
                non_tool_items_to_keep.find(slot.GetItemID()) != non_tool_items_to_keep.cend() ||
                collected_items.find(slot.GetItemID()) != collected_items.cend() ||
                AssetsManager::getInstance().GetItem(slot.GetItemID())->GetToolType() != ToolType::None)
            {
                continue;
            }
            slots_to_throw.push_back(idx);
        }
    }

    for (const short idx : slots_to_throw)
    {
        DropItemsFromContainer(client, Window::PLAYER_INVENTORY_INDEX, idx);
    }

    // Jump
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->Jump();
    }

    // Wait to be above start block
    start = std::chrono::steady_clock::now();
    while (true)
    {
        // Something went wrong during jumping
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 2000)
        {
            LOG_WARNING("Timeout waiting for jump above 1 trying to clean inventory");
            return Status::Failure;
        }
        {
            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
            if (local_player->GetY() - init_position.y >= 1.0f)
            {
                break;
            }
        }
        client.Yield();
    }

    // Put lava below
    if (SetItemInHand(client, "minecraft:lava_bucket") != Status::Success)
    {
        LOG_WARNING("Error trying to put lava bucket in right hand");
        return Status::Failure;
    }

    // Use item on
    std::shared_ptr<ProtocolCraft::ServerboundUseItemOnPacket> use_item_on = std::make_shared<ProtocolCraft::ServerboundUseItemOnPacket>();
    use_item_on->SetLocation((block_position + Position(0, -1, 0)).ToNetworkPosition());
    use_item_on->SetDirection(static_cast<int>(Direction::Up));
    use_item_on->SetCursorPositionX(0.5f);
    use_item_on->SetCursorPositionY(1.0f);
    use_item_on->SetCursorPositionZ(0.5f);
#if PROTOCOL_VERSION > 452
    use_item_on->SetInside(false);
#endif
    use_item_on->SetHand(static_cast<int>(Hand::Right));
#if PROTOCOL_VERSION > 758
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        use_item_on->SetSequence(world->GetNextWorldInteractionSequenceId());
    }
#endif
    network_manager->Send(use_item_on);
    // Use item
    std::shared_ptr<ProtocolCraft::ServerboundUseItemPacket> use_item = std::make_shared<ProtocolCraft::ServerboundUseItemPacket>();
    use_item->SetHand(static_cast<int>(Hand::Right));
#if PROTOCOL_VERSION > 758
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        use_item->SetSequence(world->GetNextWorldInteractionSequenceId());
    }
#endif
    network_manager->Send(use_item);

    // Wait for server to confirm block is lava
    start = std::chrono::steady_clock::now();
    while (true)
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 2000)
        {
            LOG_WARNING("Timeout waiting for lava trying to clean inventory");
            return Status::Failure;
        }
        {
            std::lock_guard<std::mutex> lock(world->GetMutex());
            const Block* block = world->GetBlock(block_position);
            if (block != nullptr && block->GetBlockstate()->GetName() == "minecraft:lava")
            {
                break;
            }
        }
        client.Yield();
    }

    // Get back lava in bucket
    if (SetItemInHand(client, "minecraft:bucket") != Status::Success)
    {
        // Press F to pay respect
        LOG_WARNING("Error trying to put empty bucket in right hand. It was an honour.");
        return Status::Failure;
    }

#if PROTOCOL_VERSION > 758
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        use_item_on->SetSequence(world->GetNextWorldInteractionSequenceId());
        use_item->SetSequence(world->GetNextWorldInteractionSequenceId());
    }
#endif
    network_manager->Send(use_item_on);
    network_manager->Send(use_item);

    if (SortInventory(client) == Status::Failure)
    {
        // Minor error, don't interrupt the tree ticking operation but log it anyway
        LOG_INFO("Error trying to sort inventory while picking items");
    }

    // Wait to be back on ground
    start = std::chrono::steady_clock::now();
    while (true)
    {
        // Something went wrong during waiting on ground
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 2000)
        {
            LOG_WARNING("Timeout waiting for on ground trying to clean inventory");
            return Status::Failure;
        }
        {
            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
            if (local_player->GetOnGround())
            {
                break;
            }
        }
        client.Yield();
    }

    return Status::Success;
}

Status MoveToNextLayer(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    const int last_layer = blackboard.Get<Position>("Eater.end_block").y;
    const int current_layer = blackboard.Get<int>("Eater.current_layer");
    const int bot_index = blackboard.Get<int>("Eater.bot_index");

    // We reached the end
    if (current_layer == last_layer)
    {
        blackboard.Set<bool>("Eater.done", true);
        return Status::Failure;
    }
    else
    {
        if (bot_index == 0)
        {
            LOG_INFO("Move to layer " << current_layer - 1);
        }
        blackboard.Set<int>("Eater.current_layer", current_layer - 1);
    }

    return Status::Success;
}

Status PrepareLayer(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();
    std::shared_ptr<World> world = client.GetWorld();

    const Position& start = blackboard.Get<Position>("Eater.start_block");
    const Position& end = blackboard.Get<Position>("Eater.end_block");
    const int current_layer = blackboard.Get<int>("Eater.current_layer");
    const Position& ladder_pillar = blackboard.Get<Position>("Eater.ladder_pillar");
    const std::string& temp_block = blackboard.Get<std::string>("Eater.temp_block");
    Position current_pillar = ladder_pillar;
    Position current_ladder = blackboard.Get<Position>("Eater.ladder");

    std::queue<std::pair<Position, ActionType>> action_queue;
    
    // Special case, once all the layers above ground are done, remove ugly pillar
    if (current_layer == ladder_pillar.y)
    {
        for (int y = start.y; y > ladder_pillar.y; --y)
        {
            current_pillar.y = y;
            action_queue.push({ current_pillar, ActionType::BreakPillar });
        }
    }

    // Place ladder up to current layer
    if (current_layer > ladder_pillar.y)
    {
        for (int y = ladder_pillar.y + 1; y <= current_layer; ++y)
        {
            current_pillar.y = y;
            current_ladder.y = y;
            action_queue.push({ current_pillar, ActionType::PlacePillarBlock });
            action_queue.push({ current_ladder, ActionType::PlaceLadderBlock });
        }
    }
    // Place ladder down to current layer
    else
    {
        for (int y = ladder_pillar.y; y >= current_layer; --y)
        {
            current_pillar.y = y;
            current_ladder.y = y;
            action_queue.push({ current_pillar, ActionType::PlacePillarBlock });
            action_queue.push({ current_ladder, ActionType::PlaceLadderBlock });
        }
    }

    blackboard.Set<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue", action_queue);
    return Status::Success;
}

Status PlanLayerFluids(SimpleBehaviourClient& client)
{
    std::shared_ptr<World> world = client.GetWorld();

    Blackboard& blackboard = client.GetBlackboard();
    const Position& start = blackboard.Get<Position>("Eater.start_block");
    const Position& end = blackboard.Get<Position>("Eater.end_block");
    const int current_layer = blackboard.Get<int>("Eater.current_layer");
    const PlayerDiggingFace ladder_face = blackboard.Get<PlayerDiggingFace>("Eater.ladder_face");
    Position layer_entry = blackboard.Get<Position>("Eater.ladder");
    layer_entry.y = current_layer;


    // Fluids pass
    // Get all fluid blocks
    // -1/+1 to avoid leaking from the sides
    std::unordered_set<Position> blocks_fluids = CollectBlocks(world, start + Position(-1, 0, -1), end + Position(1, 0, 1), current_layer, true, false);
    blocks_fluids.insert(layer_entry);
    std::unordered_map<Position, std::unordered_set<Position>> additional_neighbours_fluids;
    const std::vector<std::unordered_set<Position>> components_fluids = GroupBlocksInComponents(start - Position(1, 0, 1), end + Position(1, 0, 1), layer_entry, client, blocks_fluids, &additional_neighbours_fluids);
    const std::vector<Position> blocks_to_add_fluids = GetBlocksToAdd(components_fluids, layer_entry, start, end);
    const std::unordered_set<Position> blocks_to_fill_fluids = FlattenComponentsAndAdditionalBlocks(components_fluids, blocks_to_add_fluids);
    std::vector<Position> ordered_blocks_to_place_fluids = ComputeBlockOrder(blocks_to_fill_fluids, layer_entry, ladder_face, additional_neighbours_fluids);
    std::reverse(ordered_blocks_to_place_fluids.begin(), ordered_blocks_to_place_fluids.end());

    if (ordered_blocks_to_place_fluids.size() != blocks_to_fill_fluids.size())
    {
        LOG_WARNING("Ordered blocks to place have a different size than blocks to fill: " << ordered_blocks_to_place_fluids.size() << " VS " << blocks_to_fill_fluids.size());
        return Status::Failure;
    }

    std::queue<std::pair<Position, ActionType>> action_queue;
    for (const Position& p : ordered_blocks_to_place_fluids)
    {
        // Don't replace the ladder...
        if (p == layer_entry)
        {
            continue;
        }
        action_queue.push({ p, ActionType::FillFluidBlock });
    }

    blackboard.Set<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue", action_queue);

    return Status::Success;
}

Botcraft::Status PlanLayerNonWalkable(Botcraft::SimpleBehaviourClient& client)
{
    std::shared_ptr<World> world = client.GetWorld();

    Blackboard& blackboard = client.GetBlackboard();
    const Position& start = blackboard.Get<Position>("Eater.start_block");
    const Position& end = blackboard.Get<Position>("Eater.end_block");
    const int current_layer = blackboard.Get<int>("Eater.current_layer");
    const PlayerDiggingFace ladder_face = blackboard.Get<PlayerDiggingFace>("Eater.ladder_face");
    Position layer_entry = blackboard.Get<Position>("Eater.ladder");
    layer_entry.y = current_layer;


    // Non solid pass
    // Get all non solid blocks
    std::unordered_set<Position> blocks_non_walkable = CollectBlocks(world, start, end, current_layer, false, false);
    blocks_non_walkable.insert(layer_entry);
    std::unordered_map<Position, std::unordered_set<Position>> additional_neighbours_not_solid;
    const std::vector<std::unordered_set<Position>> components_non_walkable = GroupBlocksInComponents(start, end, layer_entry, client, blocks_non_walkable, &additional_neighbours_not_solid);
    const std::vector<Position> blocks_to_add_non_walkable = GetBlocksToAdd(components_non_walkable, layer_entry, start, end);
    const std::unordered_set<Position> blocks_to_fill_non_walkable = FlattenComponentsAndAdditionalBlocks(components_non_walkable, blocks_to_add_non_walkable);
    std::vector<Position> ordered_blocks_to_place_non_walkable = ComputeBlockOrder(blocks_to_fill_non_walkable, layer_entry, ladder_face, additional_neighbours_not_solid);
    std::reverse(ordered_blocks_to_place_non_walkable.begin(), ordered_blocks_to_place_non_walkable.end());

    if (ordered_blocks_to_place_non_walkable.size() != blocks_to_fill_non_walkable.size())
    {
        LOG_WARNING("Ordered blocks to replace have a different size than blocks to fill: " << ordered_blocks_to_place_non_walkable.size() << " VS " << blocks_to_fill_non_walkable.size());
        return Status::Failure;
    }

    std::queue<std::pair<Position, ActionType>> action_queue;

    for (const Position& p : ordered_blocks_to_place_non_walkable)
    {
        // Don't replace the ladder...
        if (p == layer_entry)
        {
            continue;
        }
        action_queue.push({ p, ActionType::PlaceSolidBlock });
    }

    blackboard.Set<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue", action_queue);

    return Status::Success;
}

Status PlanLayerBlocks(SimpleBehaviourClient& client)
{
    std::shared_ptr<World> world = client.GetWorld();

    Blackboard& blackboard = client.GetBlackboard();
    const std::string& temp_block = blackboard.Get<std::string>("Eater.temp_block");
    const Position& start = blackboard.Get<Position>("Eater.start_block");
    const Position& end = blackboard.Get<Position>("Eater.end_block");
    const int current_layer = blackboard.Get<int>("Eater.current_layer");
    const PlayerDiggingFace ladder_face = blackboard.Get<PlayerDiggingFace>("Eater.ladder_face");
    Position layer_entry = blackboard.Get<Position>("Eater.ladder");
    layer_entry.y = current_layer;

    std::queue<std::pair<Position, ActionType>> action_queue;

    // Solid pass
    // Get all solid blocks
    std::unordered_set<Position> blocks = CollectBlocks(world, start, end, current_layer, false, true);
    blocks.insert(layer_entry);
    std::unordered_map<Position, std::unordered_set<Position>> additional_neighbours;
    const std::vector<std::unordered_set<Position>> components = GroupBlocksInComponents(start, end, layer_entry, client, blocks, &additional_neighbours);
    const std::vector<Position> blocks_to_add = GetBlocksToAdd(components, layer_entry, start, end);
    const std::unordered_set<Position> blocks_to_mine = FlattenComponentsAndAdditionalBlocks(components, blocks_to_add);
    std::vector<Position> ordered_blocks_to_mine = ComputeBlockOrder(blocks_to_mine, layer_entry, ladder_face, additional_neighbours);

    if (ordered_blocks_to_mine.size() != blocks_to_mine.size())
    {
        LOG_WARNING("Ordered blocks to mine have a different size than blocks to mine: " << ordered_blocks_to_mine.size() << " VS " << blocks_to_mine.size());
        return Status::Failure;
    }

    for (const Position& p : blocks_to_add)
    {
        action_queue.push({ p, ActionType::PlaceTempBlock });
    }
    for (const Position& p : ordered_blocks_to_mine)
    {
        // Don't replace the ladder...
        if (p == layer_entry)
        {
            continue;
        }
        action_queue.push({ p, ActionType::BreakBlock });
    }

    blackboard.Set<std::queue<std::pair<Position, ActionType>>>("Eater.action_queue", action_queue);

    return Status::Success;
}

Status BaseCampDropItems(SimpleBehaviourClient& client, const bool all_items)
{
    std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<World> world = client.GetWorld();
    std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();
    std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
    Blackboard& blackboard = client.GetBlackboard();

    const Position& drop_position = blackboard.Get<Position>("Eater.drop_position");

    StartSprinting(client);
    if (GoTo(client, drop_position + Position(0, 1, 0)) == Status::Failure)
    {
        StopSprinting(client);
        LOG_WARNING("Error trying to GoTo drop item position " << drop_position + Position(0, 1, 0));
        return Status::Failure;
    }
    StopSprinting(client);

    LookAt(client, Vector3<double>(0.5, 0, 0.5) + drop_position, true);

    // Throw all unnecessary items
    const std::unordered_set<ItemId> non_tool_items_to_keep = {
        AssetsManager::getInstance().GetItemID("minecraft:lava_bucket"),
        AssetsManager::getInstance().GetItemID("minecraft:golden_carrot"),
        AssetsManager::getInstance().GetItemID("minecraft:ladder"),
        AssetsManager::getInstance().GetItemID(blackboard.Get<std::string>("Eater.temp_block"))
    };
    std::vector<short> slots_to_throw;
    slots_to_throw.reserve(Window::INVENTORY_OFFHAND_INDEX);
    {
        std::lock_guard<std::mutex> lock_inventory(inventory_manager->GetMutex());
        std::shared_ptr<Window> player_inventory = inventory_manager->GetPlayerInventory();
        for (const auto& [idx, slot] : player_inventory->GetSlots())
        {
            // Don't throw lava bucket, food, temp block
            if (idx < Window::INVENTORY_STORAGE_START || slot.IsEmptySlot() ||
                (!all_items && non_tool_items_to_keep.find(slot.GetItemID()) != non_tool_items_to_keep.end()))
            {
                continue;
            }
            const Item* item = AssetsManager::getInstance().GetItem(slot.GetItemID());
            // Don't throw tools with more than 10% durability
            if (!all_items && item->GetToolType() != ToolType::None && Utilities::GetDamageCount(slot.GetNBT()) < 9 * item->GetMaxDurability() / 10)
            {
                continue;
            }
            slots_to_throw.push_back(idx);
        }
    }

    for (const short idx : slots_to_throw)
    {
        if (DropItemsFromContainer(client, Window::PLAYER_INVENTORY_INDEX, idx) == Status::Failure)
        {
            LOG_WARNING("Error trying drop items at base camp");
            return Status::Failure;
        }
    }

    return Status::Success;
}

Status BaseCampPickItems(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

    const std::unordered_map<std::string, int> items_to_get = {
        { "lava_bucket", 1 },
        { "shears", 1 },
        { "hoe", 1 },
        { "shovel", 1 },
        { "axe", 1 },
        { "golden_carrots", 64 },
        { "ladder", 64 },
        { "temp_block", 5 * 64 },
        { "pickaxe", 1 }
    };

    for (const auto& [s, quantity] : items_to_get)
    {
        const Position& shulker = blackboard.Get<Position>("Eater." + s + "_position");

        if (OpenContainer(client, shulker) == Status::Failure)
        {
            LOG_WARNING("Error trying to open shulkerbox at " << shulker);
            return Status::Failure;
        }

        const short shulkerbox_window_id = inventory_manager->GetFirstOpenedWindowId();
        std::shared_ptr<Window> shulkerbox_window = inventory_manager->GetWindow(shulkerbox_window_id);

        // Get the exact name of the item in this shulkerbox
        std::string item_name = "";
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            const short player_inventory_start = shulkerbox_window->GetFirstPlayerInventorySlot();
            for (const auto& [s, slot] : shulkerbox_window->GetSlots())
            {
                if (s >= player_inventory_start || slot.IsEmptySlot())
                {
                    continue;
                }
                item_name = AssetsManager::getInstance().GetItem(slot.GetItemID())->GetName();
            }
        }

        if (item_name.empty())
        {
            LOG_ERROR("Shulker box empty while looking for " << s);
            CloseContainer(client);
            return Status::Failure;
        }

        // Check how much we already have, and which slots can be transfered to the inventory
        std::vector<std::pair<short, int>> quantities_of_items;
        std::vector<short> inventory_empty_slots;
        int quantity_inventory = 0;
        const short player_inventory_first_slot = shulkerbox_window->GetFirstPlayerInventorySlot();
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            for (const auto& [s, slot] : shulkerbox_window->GetSlots())
            {
                if (s < player_inventory_first_slot)
                {
                    if (!slot.IsEmptySlot())
                    {
                        quantities_of_items.push_back({ s,slot.GetItemCount() });
                    }
                    continue;
                }
                if (slot.IsEmptySlot())
                {
                    inventory_empty_slots.push_back(s);
                    continue;
                }
                if (AssetsManager::getInstance().GetItem(slot.GetItemID())->GetName() == item_name)
                {
                    quantity_inventory += slot.GetItemCount();
                }
            }
        }

        // Transfer items into the inventory
        size_t shulker_slot_index = 0;
        size_t inventory_slot_index = 0;
        while (quantity_inventory < quantity)
        {
            if (shulker_slot_index >= quantities_of_items.size() || inventory_slot_index >= inventory_empty_slots.size())
            {
                LOG_WARNING("Not enough items or room in inventory when taking items from shulkerbox at " << shulker);
                CloseContainer(client);
                return Status::Failure;
            }

            if (SwapItemsInContainer(client, shulkerbox_window_id, quantities_of_items[shulker_slot_index].first, inventory_empty_slots[inventory_slot_index]) == Status::Failure)
            {
                LOG_WARNING("Error trying to take items from shulkerbox at " << shulker);
                CloseContainer(client);
                return Status::Failure;
            }

            quantity_inventory += quantities_of_items[shulker_slot_index].second;

            shulker_slot_index += 1;
            inventory_slot_index += 1;
        }

        if (CloseContainer(client) == Status::Failure)
        {
            LOG_WARNING("Error trying to close shulkerbox at " << shulker);
            return Status::Failure;
        }
    }

    if (SortInventory(client) == Status::Failure)
    {
        // Minor error, don't interrupt the tree ticking operation but log it anyway
        LOG_INFO("Error trying to sort inventory while picking items");
    }

    return Status::Success;
}

Botcraft::Status HasToolInInventory(Botcraft::SimpleBehaviourClient& client, const ToolType tool_type, const int min_durability)
{
    std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        const std::map<short, ProtocolCraft::Slot>& inventory_slots = inventory_manager->GetPlayerInventory()->GetSlots();
        for (const auto& [i, slot] : inventory_slots)
        {
            if (i < Window::INVENTORY_STORAGE_START || i > Window::INVENTORY_OFFHAND_INDEX || slot.IsEmptySlot())
            {
                continue;
            }

            const Item* item = AssetsManager::getInstance().GetItem(slot.GetItemID());
            if (item->GetToolType() == tool_type && Utilities::GetDamageCount(slot.GetNBT()) < item->GetMaxDurability() - min_durability)
            {
                return Status::Success;
            }
        }
    }

    return Status::Failure;
}
