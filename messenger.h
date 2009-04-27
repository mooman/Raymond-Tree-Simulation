class Messenger {
    public:
        Messenger(int);

        //send message to site
        void send (char, int);
        void deliver ();

    private:
        Queue * timeline;

        int compute_delivery_time ();
};
