class Simulator {
    public:
        Simulator (int, int);

        void start ();
        void new_event (string);

    private:
        Queue * timeline;

        int nsites;
        int max_time;
};
