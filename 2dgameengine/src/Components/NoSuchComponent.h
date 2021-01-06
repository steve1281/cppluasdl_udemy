
#ifndef NOSUCHCOMPONENT_H
#define NOSUCHCOMPONENT_H


/*  note: created so I can test HasComponent. */

class NoSuchComponent: public Component  {
    private:

    public:
        NoSuchComponent() { }
        void Initialize() override { }
        void Update(float deltaTime) override { }
        void Render() override { }
};


#endif

