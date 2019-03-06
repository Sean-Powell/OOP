package Default;

import java.util.ArrayList;

public class Restaurant {
    private final String RestaurantName;
    private final String DeliveryOption;
    private ArrayList<Item> items;
    private float profit;

    Restaurant(String name, String deliveryType){
        RestaurantName = name;
        DeliveryOption = deliveryType;
        items = new ArrayList<>();
    }

    public String getRestaurantName(){
        return RestaurantName;
    }

    String getDeliveryOption(){
        return DeliveryOption;
    }

    ArrayList<Item> getItems() {
        return items;
    }

    void addItem(Item item){
        items.add(item);
    }

    void addProfit(float income){
        profit += income;
    }

    public float getProfit(){
        return profit;
    }
}
