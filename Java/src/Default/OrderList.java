package Default;

import OOP.LinkedList;
import Observers.Observer;

public class OrderList {
    private LinkedList<Order> list;
    private Observer observer;

    private Order newOrder;

    OrderList() {
        list = new LinkedList<>();
    }

    public Order getNewOrder() {
        return newOrder;
    }

    void addToList(Order order) {
        newOrder = order;
        list.addToList(order);
        observer.update();
    }

    public float displayInfo() {
        return observer.displayInfo();

    }

     public void attach(Observer observer) {
        this.observer = observer;
    }
}
