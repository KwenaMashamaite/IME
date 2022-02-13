////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/common/PrefContainer.h"
#include <doctest.h>

TEST_CASE("ime::PrefContainer class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::PrefContainer prefContainer;

            CHECK_EQ(prefContainer.getCount(), 0);
        }
    }

    SUBCASE("addPref()")
    {
        ime::PrefContainer prefContainer;
        prefContainer.addPref(ime::Preference{"Master_Volume", ime::PrefType::Int});
        prefContainer.addPref(ime::Preference{"Player_Name", ime::PrefType::String});
        prefContainer.addPref(ime::Preference{"V_Sync", ime::PrefType::Bool});

        CHECK_EQ(prefContainer.getCount(), 3);
        CHECK(prefContainer.hasPref("Master_Volume"));
        CHECK(prefContainer.hasPref("Player_Name"));
        CHECK(prefContainer.hasPref("V_Sync"));
        CHECK_FALSE(prefContainer.hasPref(""));
        CHECK_FALSE(prefContainer.hasPref("Sound_Enable"));
    }

    SUBCASE("removePref()")
    {
        ime::PrefContainer prefContainer;
        prefContainer.addPref(ime::Preference{"Master_Volume", ime::PrefType::Int});
        prefContainer.addPref(ime::Preference{"Player_Name", ime::PrefType::String});
        prefContainer.addPref(ime::Preference{"V_Sync", ime::PrefType::Bool});

        REQUIRE(prefContainer.hasPref("Master_Volume"));
        REQUIRE_EQ(prefContainer.getCount(), 3);

        prefContainer.removePref("Master_Volume");
        CHECK_FALSE(prefContainer.hasPref("Master_Volume"));
        CHECK_EQ(prefContainer.getCount(), 2);
    }

    SUBCASE("clear()")
    {
        ime::PrefContainer prefContainer;
        prefContainer.addPref(ime::Preference{"Master_Volume", ime::PrefType::Int});
        prefContainer.addPref(ime::Preference{"Player_Name", ime::PrefType::String});
        prefContainer.addPref(ime::Preference{"V_Sync", ime::PrefType::Bool});

        REQUIRE_EQ(prefContainer.getCount(), 3);

        prefContainer.clear();
        CHECK_EQ(prefContainer.getCount(), 0);
    }

    SUBCASE("Preferences can be Saved/loaded to/from the disk")
    {
        ime::PrefContainer prefContainer;
        prefContainer.addPref(ime::Preference{"Master_Volume", ime::PrefType::UInt, 15u, "The master volume"});
        prefContainer.addPref(ime::Preference{"Player_Name", ime::PrefType::String, std::string("Kwena"), "The name of the player"});
        prefContainer.addPref(ime::Preference{"V_Sync", ime::PrefType::Bool, false, "Vertical sync enable option"});

        const std::string saveFile = "test_prefContainer.txt";
        prefContainer.save(saveFile);

        ime::PrefContainer loadedPreferences;
        REQUIRE_EQ(loadedPreferences.getCount(), 0);
        loadedPreferences.load(saveFile);

        CHECK_EQ(loadedPreferences.getCount(), 3);
        CHECK(loadedPreferences.hasPref("Master_Volume"));
        CHECK(loadedPreferences.hasPref("Player_Name"));
        CHECK(loadedPreferences.hasPref("V_Sync"));

        ime::Preference masterVolume = loadedPreferences.getPref("Master_Volume");
        CHECK_EQ(masterVolume.getKey(), "Master_Volume");
        CHECK_EQ(masterVolume.getType(), ime::PrefType::UInt);
        CHECK_EQ(masterVolume.getValue<unsigned int>(), 15u);
        CHECK_EQ(masterVolume.getDescription(), "The master volume");

        ime::Preference playerName = loadedPreferences.getPref("Player_Name");
        CHECK_EQ(playerName.getKey(), "Player_Name");
        CHECK_EQ(playerName.getType(), ime::PrefType::String);
        CHECK_EQ(playerName.getValue<std::string>(), std::string("Kwena"));
        CHECK_EQ(playerName.getDescription(), "The name of the player");
    }
}