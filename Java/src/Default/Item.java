package Default;

public class Item {
    private final String ItemName;
    private final float ItemPrice;

    Item(String name, float price){
        ItemName = name;
        ItemPrice = price;
    }

    String getItemName() {
        return ItemName;
    }

    float getItemPrice() {
        return ItemPrice;
    }
}
