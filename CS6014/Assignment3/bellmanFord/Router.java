package msd.benjones;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class Router {

    private HashMap<Router, Integer> distances;
    private String name;
    public Router(String name) {
        this.distances = new HashMap<>();
        this.name = name;
    }

    public void onInit() throws InterruptedException {

		//TODO: IMPLEMENT ME
		//As soon as the network is online,
		//fill in your initial distance table and broadcast it to your neighbors
        
        HashSet<Neighbor> neighbors = Network.getNeighbors(this);

        // fill in initial distance table
        for (Router curRouter : Network.getRouters()) {
            if (curRouter == this) {
                distances.put(curRouter, 0);
            }
            else {
                distances.put(curRouter, Integer.MAX_VALUE);
            }
        }
        
        for (Neighbor curNeighbor : neighbors) {
            distances.put(curNeighbor.router, curNeighbor.cost);
        }
        
        // broadcast it to the neighbors
        for (Neighbor curNeighbor : neighbors) {
            Message message = new Message(this, curNeighbor.router, distances);
            Network.sendDistanceMessage(message);
        }
    }

    public void onDistanceMessage(Message message) throws InterruptedException {
		//update your distance table and broadcast it to your neighbors if it changed

        if (this == message.receiver) {
            for (Router curRouter : Network.getRouters()) {
                int curDistance = message.distances.get(curRouter) + this.distances.get(message.sender);

                if (message.distances.get(curRouter) != 0 &&
                    message.distances.get(curRouter) != Integer.MAX_VALUE &&
                    curDistance < this.distances.get(curRouter) && 
                    this.distances.get(message.sender) != 0) {

                    // broadcast it to your neighbors if it changed
                    this.distances.put(curRouter, curDistance);
                    
                    Message broadcast = new Message(this, curRouter, distances);
                    Network.sendDistanceMessage(broadcast);
                }
            }
        }
    }


    public void dumpDistanceTable() {
        System.out.println("router: " + this);
        for(Router r : distances.keySet()){
            System.out.println("\t" + r + "\t" + distances.get(r));
        }
    }

    @Override
    public String toString(){
        return "Router: " + name;
    }
}
