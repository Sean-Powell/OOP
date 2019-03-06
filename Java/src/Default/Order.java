package Default;

import java.util.ArrayList;

public class Order {
    private Restaurant restaurant;
    private ArrayList<Item> list;
    private String deliveryType;
    private float totalPrice;

    Order(Restaurant restaurant, String delivery){
        this.restaurant = restaurant;
        list = new ArrayList<>();
        deliveryType = delivery;
    }

    public Restaurant getRestaurant() {
        return restaurant;
    }

    String getDeliveryType() {
        return deliveryType;
    }

    public ArrayList<Item> getList() {
        return list;
    }

    void addToItems(Item item){
        list.add(item);
        addToCost(item.getItemPrice());
    }

    private void addToCost(float cost){
        totalPrice += cost;
    }

    public float getTotalPrice() {
        return totalPrice;
    }
}
