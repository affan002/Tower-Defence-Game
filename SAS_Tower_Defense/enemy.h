class Enemy {
public:
    virtual ~Enemy() {}

    virtual void attack() = 0;
    virtual void takeDamage(int damage) = 0;
    virtual bool isDefeated() const = 0;
};