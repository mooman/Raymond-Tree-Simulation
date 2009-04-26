class Site {
    public:
        Site();

        int get_id ();

        void request ();
        void accept_request ();

    private:
        int id;
        int holder;
}
