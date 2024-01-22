/*
 * Muyuan Zhang
 * Collaborated with Gloria Dukuzeyesu
 */

package Rooms;

import Game.Adventure;
import Items.Item;

public class Garden extends Room {
    // create a self-defined room here
    // can interact with the items in the Bathroom
    protected static boolean watered_ = false;
    private Item roses = new Item("roses", "The roses are wilted.");

    public Garden() {
        super("Garden", "A garden with variable plants.");
        items_.add(roses);
    }

    @Override
    public void playerEntered() {
        // give the player a hint to water the roses if they have not done that
        if (! watered_) {
            System.out.println("The roses are wilted: they are out of water.");
        }
    }

    @Override
    public boolean handleCommand(String[] subcommands) {
        if (subcommands.length <= 1) {
            return false;
        }

        String cmd  = subcommands[0];
        String attr = subcommands[1];

        // if the command is "water roses"
        if (cmd.equals("water") && attr.equals("roses")) {
            for (Item item : Adventure.inventory) {
                // if the player has the spray bottle from the bathroom
                if (item.getName().equals("spraybottle")) {
                    // the roses are watered now
                    watered_ = true;
                    break;
                }
            }

            // if the roses are watered
            if (watered_) {
                System.out.println("You watered the roses. Thank you!");
                printMap();
            }
            // if the player do not have the spray bottle from the bathroom
            else {
                System.out.println("You don't have a spray bottle.");
            }
            return true;
        }

        // if the command is "pickup roses"
        else if (cmd.equals("pickup") && attr.equals("roses")) {
            System.out.println("You grabbed the roses.");
            // append the roses to the inventory
            Adventure.inventory.add(roses);

            return true;
        }

        return false;
    }

    // print out a map of the house if the rose is watered
    protected static void printMap() {
        System.out.println("You got a map of the house from the rose blossom!");
        System.out.println("---------------------------------------------------------------");
        System.out.println("| outside -> entrance -> hall -> stairs -> bedroom -> balcony |");
        System.out.println("---------------------------------------------------------------");
    }
}
