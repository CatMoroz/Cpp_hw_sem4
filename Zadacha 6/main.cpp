#include <iostream>
#include <string>
#include <vector>

struct Checkpoint {
    std::string name;
    double latitude;
    double longitude;
    bool mandatory;
    double penalty;
    Checkpoint(std::string n, double lat, double lon, bool mandatory, double pen = 0.0) : name(n), latitude(lat), longitude(lon), mandatory(mandatory), penalty(pen) {}
};

class CheckpointsBuilder {
public:
    virtual void setCheckpoints(const std::vector<Checkpoint*>& checkpoints) = 0;
    virtual void checkpointsInfo() = 0;
    virtual void countStats() = 0;
    virtual void reset() = 0;
};

class ConcreteCheckpointBuilder : public CheckpointsBuilder {
private:
    double totalPenalty = 0.0;
    std::vector<Checkpoint*> checkpoints;

public:
    ConcreteCheckpointBuilder() {}

    void setCheckpoints(const std::vector<Checkpoint*>& checkpoints) override
    {
        this->checkpoints = checkpoints;
    }

    void checkpointsInfo() override 
    {
        for (int i = 0; i < checkpoints.size(); i++)
        {
            auto checkpoint = checkpoints[i];
            std::cout << i + 1 << ". " + checkpoint->name + " - Coordinates: (" << checkpoint->latitude<< ", " << checkpoint->longitude << ")";
            if (!checkpoint->mandatory) 
            {
                std::cout << " - Penalty: " << checkpoint->penalty << " hours";
            }
            else 
            {
                std::cout << " - Penalty: nezachet SU";
            }
            std::cout << "\n";
        }
        
    }
    
    void countStats() override
    {
        for (int i = 0; i < checkpoints.size(); i++)
        {
            if (!checkpoints[i]->mandatory) 
            {
                totalPenalty += checkpoints[i]->penalty;
            }
        }
    }

    double getTotalPenalty() { return totalPenalty; }

    void reset() override
    {
        checkpoints = std::vector<Checkpoint*>();
        totalPenalty = 0.0;
    }

};

class Director
{
private:
    CheckpointsBuilder* builder;
public:
    Director (CheckpointsBuilder* builder) : builder(builder) {}

    void buildProduct(const std::vector<Checkpoint*>& checkpoints)
    {
        builder->setCheckpoints(checkpoints);
        builder->checkpointsInfo();
        builder->countStats();
    }
};

int main()
{
    ConcreteCheckpointBuilder* builder = new ConcreteCheckpointBuilder();
    Director d(builder);

    std::vector<Checkpoint*> checkpoints= {new Checkpoint("First", -45, 30, 1), new Checkpoint("Second", 45, 10, 0, 20), new Checkpoint("Third", -50, 16, 0, 1.5)};
    d.buildProduct(checkpoints);
    std::cout << builder->getTotalPenalty();
    builder->reset();

    delete builder;
    for (Checkpoint* c : checkpoints)
        delete c;
}