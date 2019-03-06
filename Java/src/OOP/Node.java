package OOP;

public class Node<T> {
    private Node<T> nextNode;
    private T data;

    Node(T _data){
        data = _data;
    }

    public T getData() {
        return data;
    }

    public void setNextNode(Node<T> nextNode) {
        this.nextNode = nextNode;
    }

    public Node<T> getNextNode() {
        return nextNode;
    }
}