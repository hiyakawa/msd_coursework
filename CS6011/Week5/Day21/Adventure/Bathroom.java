/*
 * Gloria Dukuzeyesu
 * Collaborated with Muyuan Zhang
 */

package Rooms;

import Game.Adventure;
import Items.Item;

public class Bathroom extends Room {
    private Item sprayBottle = new Item("spraybottle", "Some times, I wet my plants...");

    public Bathroom() {
        super("Bathroom", "Wash away your troubles with bubble bath.");
        items_.add(sprayBottle);
    }

    public boolean handleCommand(String[] subcommands) {
        if (subcommands.length <= 1) {
            return false;
        }

        String cmd = subcommands[0];
        String attr = subcommands[1];

        // if the command is "pickup spraybottle"
        if (cmd.equals("pickup") && attr.equals("spraybottle")) {
            System.out.println("You grabbed the spray bottle.");
            // append the sprayBottle to the inventory
            Adventure.inventory.add(sprayBottle);

            return true;
        }

        // if the command is "water roses"
        else if (cmd.equals("water") && attr.equals("roses")) {
            for (Item item : Adventure.inventory) {
                // if the player has the roses from the garden
                if (item.getName().equals("roses")) {
                    // the roses are watered now
                    Garden.watered_ = true;
                    break;
                }
            }

            // if the roses are watered
            if (Garden.watered_) {
                System.out.println("You watered the roses. Thank you!");
                Garden.printMap();
            }
            // if the player do not have the roses from the garden
            else {
                System.out.println("You don't have anything to water.");
            }
            return true;
        }

        return false;
    }
}
