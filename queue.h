class Queue {
    public:

    Queue();
    void enqueue (void *);
    void * dequeue ();

    private:

    struct queue {
        void * obj;
        queue * next;
    };

    queue * head;
    queue * tail;
};
