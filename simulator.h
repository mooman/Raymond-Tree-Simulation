class Simulator {
    public:
        Simulator (int, int);

        void start ();
        void new_event (string);
        void new_event (int, int, int);
        int get_current_time ();

    private:
        Queue * timeline;
        Messenger * m;

        int nsites;
        int max_time;
        int current_time;
};
