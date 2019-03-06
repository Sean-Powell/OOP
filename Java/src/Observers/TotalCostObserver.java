package Observers;

import Default.Orders;

public class TotalCostObserver extends Observer{
    private float totalCost = 0;
    private Orders orders;

    public TotalCostObserver(Orders orders){
        this.orders = orders;
        this.orders.attach(this);
    }

    @Override
    public void update(){
        totalCost += orders.getNewOrderList().displayInfo();
    }

    @Override
    public float displayInfo(){
        return totalCost;
    }
}
