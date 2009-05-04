#ifndef SITE_H_
#define SITE_H_

class Site {
    public:
        // constructor
        Site();

        int get_id ();
        void request ();
        void accept_request ();
        int id;
        Site* left;
        Site* right;

    private:
        int holder;
};

#endif /*SITE_H_*/
