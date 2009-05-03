class Messenger {
    public:
        Messenger(int);

        //send message to site
        void send (int, int);

    private:
        Queue * timeline;
        int * weighted_delays;
        const int wd_size;

        Simulator * s;

        int compute_delivery_delay ();
};
