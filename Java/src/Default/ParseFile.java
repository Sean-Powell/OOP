package Default;

import Observers.OrderListObserver;
import Observers.TotalCostObserver;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


class ParseFile {
    //read file line by line, split line by space, check for keywords
    void parseFile(String fileLocation) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(new File(fileLocation)));
        String line;
        ArrayList<Restaurant> restaurants = new ArrayList<>();

        Orders orders = new Orders();
        new TotalCostObserver(orders);

        while ((line = br.readLine()) != null) {
            String[] token = line.split(" ");
            switch (token[0]) {
                case "BeginRestaurant":
                    restaurants.add(parseRestaurant(token, br));//extracts the information about each restaurant
                    break;
                case "BeginOrderList":
                    OrderList orderList = new OrderList();
                    new OrderListObserver(orderList);//creates new observer
                    boolean foundEnd = false;
                    while((line = br.readLine()) != null){//loops until end of file or till end of the order list
                        token = line.split(" ");
                        if(token[0].equals("EndOrderList")){
                            orders.addOrderList(orderList);
                            foundEnd = true;
                            break;
                        }else if(token[0].equals("BeginOrder")){
                            orderList.addToList(parseSubOrder(token, br, restaurants));//extracts the sub oder
                        }
                    }

                    if(foundEnd){
                        break;
                    }else {
                        throw new Exception("Missing EndOrderList");
                    }
                case "": //blank line ignore
                    break;
                default:
                    throw new Exception("Unknown keyword in file");
            }
        }

        orders.displayInfo();
        br.close();
    }

    private Order parseSubOrder(String[] token, BufferedReader br, ArrayList<Restaurant> restaurants) throws Exception{
        String line;
        Restaurant orderingFrom = null;
        for(Restaurant x: restaurants){
            if(x.getRestaurantName().equals(token[1])){
                orderingFrom = x;
                break;
            }
        }
        if(orderingFrom == null){
            throw new Exception("Default.Restaurant with name " + token[1] + " not found");
        }

        Order order = new Order(orderingFrom, token[2]);

        while((line = br.readLine()) != null){
            token = line.split(" ");
            if(token[0].equals("EndOrder")){
                break;
                }else if(token[0].equals("OrderItem")){
                    Item item = null;
                    for(Item i: orderingFrom.getItems()){
                        if(i.getItemName().equals(token[1])){
                        item = i;
                        break;
                    }
                }
                if(item == null){
                    throw new Exception("Default.Item with name " + token[1] + " not found");
                }
                order.addToItems(item);
            }
        }

        if(orderingFrom.getDeliveryOption().equals(order.getDeliveryType()) || orderingFrom.getDeliveryOption().equals("both")) {
            orderingFrom.addProfit(order.getTotalPrice());
            return order;
        }else{
            throw new Exception("Invalid delivery option for this restaurant");
        }
    }

    private Restaurant parseRestaurant(String[] token, BufferedReader br) throws IOException{
        String line;
        Restaurant restaurant = new Restaurant(token[1], token[2]);
        while((line = br.readLine()) != null){
            token = line.split(" ");
            if(token[0].equals("EndRestaurant")){
                break;
            }else if(token[0].equals("Default.Item")){
                restaurant.addItem(new Item(token[1], Float.parseFloat(token[2])));
            }
        }
        return restaurant;
    }
}
