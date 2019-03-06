package OOP;

public class LinkedList<T> {
    private int length;
    private Node<T> firstNode;

    public LinkedList(){
        length = 0;
    }

    public void addToList(T data){
        if(length == 0){
            firstNode = new Node<>(data);
        }else{
            Node<T> node = firstNode;
            for(int i = 0; i < length - 1; i++){
                node = node.getNextNode();
            }
            Node<T> newNode = new Node<>(data);
            node.setNextNode(newNode);
        }
        length++;
    }

    public T getFromList(int index){
        if(index > length) {
            throw new IndexOutOfBoundsException();
        }else{
            Node<T> node = firstNode;
            for(int i = 0; i < index - 1; i++){
                node = node.getNextNode();
            }
            return node.getData();
        }
    }
}
