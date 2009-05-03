class Queue {
    public:
        Queue();
        void enqueue (void *);
        void * dequeue ();
        bool empty ();

    private:
        struct queue {
            void * obj;
            queue * next;
        };

        queue * head;
        queue * tail;
};
