#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#define PI 3.1415
#define REFLEX_ARC PI

#include <QWidget>
#include <QVector>
#include <QTextStream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class SimulationManager; }
QT_END_NAMESPACE

class SimulationManager : public QWidget
{
    Q_OBJECT

public:
    SimulationManager(QWidget *parent = nullptr);
    ~SimulationManager();

private slots:


    void on_importButton_clicked();

    void on_chooseHerb_valueChanged(int i);

    void on_chooseCarn_valueChanged(int i);

    void on_chooseGen_valueChanged(int arg1);

    void on_progress_clicked(bool checked);

    void on_loop_clicked(bool checked);

    void timeOutSlot();

    void on_simulate_clicked(bool checked);

    void on_frameRate_valueChanged(int arg1);

private:

    struct entity{
        int x;
        int y;
        float angle;
    };

    struct individual{
        int plant_const;
        int herb_const;
        int carn_const;

        int plant_weight;
        int herb_weight;
        int carn_weight;

        int search_height_limit;
        int search_height;

        int speed;

        int energy;
        int health;
        int hurt;
    };


    void readWanderers(QTextStream* in);
    void readCarnivores(QTextStream* in);
    void openWanderers();
    void openCarnivores();

    void simulate();

    void initialize_populations();
    int check_disponibility(int x, int y);

    void genetic_rotation(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop, int index);
    float calculate_angle(int x, int y, int xobs, int yobs, float dir_angle);

    void obstacles_bfs(int startx, int starty, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn);
    void obstacles_bfs_restricted(int startx, int starty, bool* b_plant, bool* b_wond, bool* b_carn, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn, int height);

    void move_wanderers(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop);
    void move_carnivores(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop);

    bool check_for_obstacles(int x0, int y0, float Cos, float Sin, int speed, int *type);
    bool carnivores_check_for_obstacles(int x0, int y0, float Cos, float Sin, int speed, int *type);

    void new_plants();

    cv::Mat print_img();

    Ui::SimulationManager *ui;

    QString fileName;
    int gen;
    int herb_pop;
    int carn_pop;
    int plants_pop;

    bool loop;
    bool do_simulate;

    QVector<QVector<individual>> herbivores;
    QVector<QVector<individual>> carnivores;

    QTimer *DataTimer;

    const char* environment;

    int timeOutCount;
    int gen_interval;

    int X;
    int Y;
    int** matrix;
    int RADIUS;
    int sim_gen;

    QVector<entity> herb_sim;
    QVector<entity> carn_sim;
    QVector<entity> plant_sim;


};
#endif // SIMULATIONMANAGER_H
