/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <list>
#include "game_party_base.h"

void Game_Party_Base::GetBattlers(std::vector<Game_Battler*>& out) {
	int count = GetBattlerCount();
	for (int i = 0; i < count; ++i) {
		Game_Battler* battler = &(*this)[i];
		out.push_back(battler);
	}
}

void Game_Party_Base::GetAliveBattlers(std::vector<Game_Battler*>& out) {
	int count = GetBattlerCount();
	for (int i = 0; i < count; ++i) {
		Game_Battler* battler = &(*this)[i];
		if (!battler->IsDead()) {
			out.push_back(battler);
		}
	}
}

void Game_Party_Base::GetDeadBattlers(std::vector<Game_Battler*>& out) {
	int count = GetBattlerCount();
	for (int i = 0; i < count; ++i) {
		Game_Battler* battler = &(*this)[i];
		if (battler->IsDead()) {
			out.push_back(battler);
		}
	}
}

Game_Battler* Game_Party_Base::GetNextAliveBattler(Game_Battler* battler) {
	std::vector<Game_Battler*> battlers;
	GetBattlers(battlers);

	std::vector<Game_Battler*>::const_iterator it;
	it = std::find(battlers.begin(), battlers.end(), battler);

	if (it == battlers.end()) {
		return NULL;
	}

	for (++it; it != battlers.end(); ++it) {
		Game_Battler* b = *it;
		if (!b->IsDead()) {
			return b;
		}
	}

	// None found after battler, try from the beginning now
	for (it = battlers.begin(); *it != battler; ++it) {
		Game_Battler* b = *it;
		if (!b->IsDead()) {
			return b;
		}
	}

	return NULL;
}

Game_Battler* Game_Party_Base::GetRandomAliveBattler() {
	std::vector<Game_Battler*> battlers;
	GetAliveBattlers(battlers);
	if (battlers.empty()) {
		return NULL;
	}
	int ra = rand() / (RAND_MAX / battlers.size() + 1);
	return battlers[ra];
}

Game_Battler* Game_Party_Base::GetRandomDeadBattler() {
	std::vector<Game_Battler*> battlers;
	GetDeadBattlers(battlers);
	if (battlers.empty()) {
		return NULL;
	}

	return battlers[rand() / (RAND_MAX / battlers.size() + 1)];
}

bool Game_Party_Base::IsAnyAlive() {
	return GetRandomAliveBattler() != NULL;
}
