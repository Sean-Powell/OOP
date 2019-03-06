package Observers;

import Default.OrderList;
import Default.Restaurant;

public class OrderListObserver extends Observer{
    private float totalSpent = 0;
    private float mostProfit = Float.MIN_VALUE;
    private Restaurant mostProfitable = null;
    private OrderList orderList;

    public OrderListObserver(OrderList orderList){
        this.orderList = orderList;
        this.orderList.attach(this);
    }

    @Override
    public void update(){
        totalSpent += orderList.getNewOrder().getTotalPrice();

        Restaurant tempRest = orderList.getNewOrder().getRestaurant();
        if(mostProfit < tempRest.getProfit()){
            mostProfit = tempRest.getProfit();
            mostProfitable = tempRest;
        }
    }

    @Override
    public float displayInfo(){
        System.out.println("Most profitable restaurant " + mostProfitable.getRestaurantName());
        System.out.println("Total spent at all restaurants in Default.Order List: " + totalSpent);
        return totalSpent;
    }
}
