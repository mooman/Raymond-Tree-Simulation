class Site {
    public:
        Site();
        Site(Messenger *);

        int get_id ();
        void process_event(Event *);

    private:
        int id;
        int holder;
}
