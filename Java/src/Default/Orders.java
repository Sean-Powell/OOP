package Default;

import Observers.Observer;

import java.util.ArrayList;

public class Orders {
    private ArrayList<OrderList> orders = new ArrayList<>();
    private Observer observer;


    private OrderList newOrderList;

    public OrderList getNewOrderList() {
        return newOrderList;
    }

    public void attach(Observer observer) {
        this.observer = observer;
    }

    void addOrderList(OrderList orderList) {
        orders.add(orderList);
        newOrderList = orderList;
        observer.update();
    }

    public ArrayList<OrderList> getOrders() {
        return orders;
    }

    void displayInfo(){
        System.out.println("Total ammount spent: " + observer.displayInfo());
    }
}
