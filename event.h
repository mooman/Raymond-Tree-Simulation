class Event {
    public:
        Event(string);
        Event(int, int, int, int);

        int get_time ();
        int get_site ();
        int get_from ();
        char get_action ();

    private:
        int time;
        int site;
        int from;
        int action;

        void parse (string);
};
