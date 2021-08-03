
#include<iostream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

using namespace std;
// z_viewPoint is used to transfer the objects far away from origin. z_dis is also for the z_direction view.
float tx=0,ty=0,z_dis=100,z_viewPoint= -120;
unsigned char mainKey = 'a'; // mainKey for display function. 'a' for run the program by default.

GLUquadricObj *rocketBody, *rocketPlate;
GLfloat pos[]= { -35, -8, 5, 1};                        //light position
GLfloat amb [] = {0.3, 0.3, 0.3, 1.0};                //Ambient intensity
GLfloat front_amb_diff[]= {0.7, 0.5, 0.1,1.0};    //Front side property
GLfloat back_amb_diff[]= {0.4,0.7,0.1,1.0};        //Back side property
GLfloat spe[]= {0.25,0.25,0.25,1.0};            //Property for front and back
GLfloat theta=0,alpha=0, dt=0.5;

//This function draw the cylinder in the middle of the rocket body. Use glutSolidCube to draw the windows on the cylinder.
void rocket_body(){
    glPushMatrix ();
    rocketBody = gluNewQuadric();
    gluQuadricDrawStyle(rocketBody, GLU_FILL);
    gluQuadricNormals(rocketBody, GLU_SMOOTH);
    gluQuadricOrientation(rocketBody, GLU_OUTSIDE);
    
    glColor3f(1, 0.51, 0.04);// color for the body cylinder.
    glTranslated(7.5, -18, z_viewPoint);
    glRotated(-90, 1, 0, 0);
    gluCylinder(rocketBody, 4.5, 4.5, 30, 32, 32);
    
    // Code below draw 5 black windows on rocket body
    glColor3f(0, 0, 0);
    int windows[5]={-5, -10,-15, -20,-25};     // 5 windows in y direction
    for(int i=0; i<5; i++){
        glPushMatrix ();
        glRotated(90, 0, 0, 1);//need to rotate twice(around x, then arond z)to keep the same direction with the rocket body.
        glRotated(-90, 1, 0, 0);
        glTranslated(0, windows[i], 0);
         // scale the cube on x_axis. each cube is a little bit longer than the raduis of the cylinder. Therefore, we can see them outside the cylinder.
        glScalef(6.45, 1, 1);
         // use cube to draw windows. 5 cubes inside the cylender.
        glutSolidCube(1.4);
        glPopMatrix();
    }
    
    glPopMatrix();
}

//This function draw a sphere at the bottom of the cylinder as the bottom of the rocket.
void rocket_bottom(){
    glColor3f(0, 0.51, 0.641);
    glPushMatrix();
    glTranslated(7.5, -18, z_viewPoint);// for spherical bottom of the rocket
    glRotated(-90, 1, 0, 0);                    // Rotate Cylinder along X-axis to make it look vertical
    glutSolidSphere(4.5, 32, 32);
    glPopMatrix();
}

//This function draw a cone on top of the cylinder as the top of the rocket.
void rocket_top(){
    glColor3f(0.482, 0.937, 0.145);
    glPushMatrix();
    glTranslated(7.5, 12, z_viewPoint);
    glRotated(-90, 1, 0, 0);
    glutSolidCone(4.5,10.0,32,32);
    glPopMatrix();
}


//This function use glupartialDisk() to draw the three rocket plates at the bottom of the rocket.
void rocket_plates(){
    rocketPlate = gluNewQuadric();
    gluQuadricDrawStyle(rocketPlate, GLU_FILL);
    gluQuadricNormals(rocketPlate, GLU_SMOOTH);
    gluQuadricOrientation(rocketPlate, GLU_OUTSIDE);
    glColor3f(1,0,0);
    
    //draw the right most plate. This plate is not in the most proper position even thought tried a lot of rotations.
    glPushMatrix ();
    glTranslated(7.5, -15.5, z_viewPoint);
    glRotatef(45, 0, 1, 0);
    glRotatef(160, 1, 0, 0);
    gluPartialDisk(rocketPlate,4.5,18, 10, 5, 0, 30);
    glPopMatrix();
    
    //draw the back plate.
    glPushMatrix ();
    glTranslated(7.5, -15.5, z_viewPoint);
    glRotatef(160, 1, 0, 0);// then rotated around x axis for 150 degree.
    glRotatef(-90, 0, 1, 0);//first rotated around y axis for -90 degree.
    gluPartialDisk(rocketPlate,4.5,18, 10, 5, 0, 30);
    glPopMatrix();
    
    //draw the left most plate.
    glPushMatrix ();
    glTranslated(7.5, -15.5, z_viewPoint);
    glRotatef(225, 0, 1, 0);
    glRotatef(160, 1, 0, 0);
    gluPartialDisk(rocketPlate,4.5,18, 10, 5, 0, 30);
    glPopMatrix();
}
///showing the full body function assemble the rocket top(cone), body(cylinder),bottom(sphere) and plates(3 partial disks) together.
void rocket_assembly() {
    
    rocket_top();
    rocket_plates();
    rocket_body();
    rocket_bottom();
}

//seprate the rocket to top, body, bottom and plates.
void rocket_seperate(){
    
    theta = theta-30;
    glPushMatrix();
    glRotated(theta, 1, -1, 0);
    rocket_top();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(theta, -1, 0, 1);
    rocket_body();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(theta, 1, 0, 0);
    rocket_bottom();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(theta/3, 1, 0, 0);
    rocket_plates();
    glPopMatrix();
    
    theta = theta +30; // Resetting theta
}

//This function draw the stars.
void stars(void){
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(30, -25, -210);
    glutSolidOctahedron();
    glPopMatrix();
    
    
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslated(-20, 10, -300);
    glutSolidSphere(2.5, 32, 32);
    glPopMatrix();


    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(35.5,20 , -250);
    glutSolidSphere(2, 32, 32);
    glPopMatrix();
    
     glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslated(-10, 25, -550);
    glutSolidIcosahedron();
    glPopMatrix();
    
    
    
    glColor3f(1.5,0.5,0);
    glPushMatrix();
    glTranslated(35.5,-20 , -200);
    glRotated(-90, 1, 0, 0);
    glutSolidSphere(1.5, 32, 32);
    glPopMatrix();
    
     
    glColor3f(1.5,0.5,0);
    glPushMatrix();
    glTranslated(-35.5,100 , -600);
    glRotated(-90, 1, 0, 0);
    glutSolidSphere(1.5, 32, 32);
    glPopMatrix();
    
   
      glColor3f(0,0,1);
    glPushMatrix();
    glTranslated(-10, 0, -450);
    glutSolidOctahedron();
    glPopMatrix();
    
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(-50, -10, -450);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glColor3f(0.937, 0.145, 0.145);
    glPushMatrix();
    glTranslated(-15.5, -2.5, -200);
    glutSolidSphere(1.15, 32, 32);
    glPopMatrix();

    glColor3f(0.145, 0.882, 0.937);
    glPushMatrix();
    glTranslated(-5.5, 5, -200);
    glutSolidSphere(2, 32, 32);
    glPopMatrix();
    
      glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(-50, 0, 0);
    glutSolidIcosahedron();
    glPopMatrix();
    
    
     glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslated(-10, 0, -300);
    glutSolidOctahedron();
    glPopMatrix();
    
     glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(40, 0, -670);
    glutSolidIcosahedron();
    glPopMatrix();
}

//Use mainKey in display function to make sure that idle display and keyboard display can be switched smoothly.
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); // Preserve the CTM that Puts the objects along the z_viewPoint.
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    switch (mainKey) {
        case 'a':{
            glPushMatrix();
            glTranslated(0, 0, z_dis - 300);
            stars(); // show stars far away.
            
            glPopMatrix();
            z_dis += 0.8; //stars go closer to eye. Build the effect of moving.
            
            if(theta>359 && theta < 360)  //reset rotation angle and z_dis.
            {
                z_dis = 100;
                z_viewPoint = -120;
            }
            
            else if(theta < 46) {
                glPushMatrix();
                glTranslated(tx, ty, 0);
                glTranslated(6.5, 0, z_viewPoint);
                glRotated(-theta*1.1, 1, 0, 0);// rotate around x_axis, goes far away from origin(eye).
                glTranslated(-6.5, 0, z_viewPoint*(-1));
                rocket_assembly();
                glPopMatrix();
            }
            
            else{
                glPushMatrix();
                glTranslated(6.5, 0, z_viewPoint);
                glRotated(-50, 1, 0, 0); //rotate around x_axis, goes far away from origin(eye).
                glTranslated(-6.7,0,z_viewPoint*(-1));//moving forward far away from eye.
                
                glPushMatrix();
                glTranslated(6.5, 0, z_viewPoint);
                glRotated(alpha, 0, 1, 0);
                alpha = alpha+2;
                glTranslated(-6.5, 0, z_viewPoint*(-1));
                rocket_assembly();
                if(z_dis > 3000)
                    z_viewPoint-=0.10;
                glPopMatrix();
                
                glPopMatrix();
            }
            break;
        }
                
        case 'b': {
            glPushMatrix();                 //Preserve CTM for object
            glTranslated(tx, ty, 0);
            glTranslated(6.5, 0, z_viewPoint);
            glRotated(theta, 1, 1, 1);
            glTranslated(-6, 0, z_viewPoint*(-1));
            rocket_seperate();
            stars();
            glPopMatrix();
            break;
        }
         case 'c': {
            glPushMatrix();                 //Preserve CTM for object
            glTranslated(tx, ty, 0);
            glTranslated(6.5, 0, z_viewPoint);
            glRotated(-40, 1, 0, 0);
            glTranslated(-6, 0, z_viewPoint*(-1));
            rocket_assembly();
            stars();
            glPopMatrix();
            break;
        }
    }
    
    glPopMatrix();
    glutSwapBuffers();
}
    

void keyboard(unsigned char key, int x, int y){
    if(key=='a'||key=='b'||key=='c'){
        mainKey = key;                // main key used in display function
        if (key=='c') theta = 45;
        else if(key == 'b')
        {
            theta = 30;
        }
    }
    else{
        mainKey='a';
    }
    glutPostRedisplay();
}

void idle(void){
    theta = (theta <360) ? theta+dt:dt;  //increment rotation angle
    tx= tx - 0.02; //adjust the x and y distance for moving effect
    ty = ty + 0.02;
    glutPostRedisplay();
}

void output_menu(){
    fprintf(stdout, "Rocket 3D Manual:BARNABAS OMBAKI NYANSIMERA");
     cout<<"\n\nThe program is run by default."<<endl;
     cout<<"\033[0;32;32mcontrolls coming soon.\n\n"<<endl;
     cout <<"please Press 'a' to run the program again.\n\n"<<endl;
        cout <<"please Press 'b' to separate the rocket body.\n\n"<<endl;
           cout <<"please Press 'c' to show the stars,rocket moving.\n\n"<<endl;
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("3D ROCKET BY BARNABAS OMBAKI NYANSIMERA ");
    glClearColor(0, 0, 0, 1);       //sets background color (r,g,b,alpha) for the window.
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 10, 10000);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);    //Front side
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);      //Back side
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);                //Front and back
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 45);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);     //light source
    glEnable(GL_NORMALIZE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glLightfv(GL_LIGHT0, GL_POSITION, pos); //light postion is affected by current modelview
    glEnable(GL_LIGHTING);     //enable light
    glEnable(GL_LIGHT0);         //enable gl_light0
    glEnable(GL_COLOR_MATERIAL);// Enable Color Material

    
    output_menu();
    glutDisplayFunc(display);        //register display call back function
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
