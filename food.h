#ifndef FOOD_H
#define FOOD_H

class Ifood {
private:
    std::pair<int, int> position;

public:
    Ifood();
    virtual std::pair<int, int> getPosition() = 0; // <<pure>>
    virtual ~Ifood();
};

class NormalFood : public Ifood {
public:
    std::pair<int, int> getPosition() override;
    ~NormalFood() override;
};

class SuperFood : public Ifood {
public:
    std::pair<int, int> getPosition() override;
    ~SuperFood() override;
};

#endif // FOOD_H
