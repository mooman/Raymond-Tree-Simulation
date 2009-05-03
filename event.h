class Event {
    public:
        Event(string);
        Event(int, int, int);

        int get_time ();
        int get_site ();
        char get_action ();

        void execute ();

    private:
        int time;
        int site;
        int compute_duration;
        int action;

        void parse (string);
};
