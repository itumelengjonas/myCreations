#include <GL/glut.h>
#include <string.h>
#include <vector>
#include <cmath>

// Constants
const int windowWidth = 800;
const int windowHeight = 600;
const float angle = 90.0f;


float armAngle = 0.0f; // Angle for robot arm movement
float legAngle = 0.0f; // Angle for robot leg movement
bool armIncreasing = true;
bool legIncreasing = true;

// Struct to represent a ray
struct Ray {
    float x, y, z;
    float length;
};

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.5, 0.7, 0.9, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Function to draw strings on the screen
void drawString(float x, float y, float z, const char* string) {
    glRasterPos3f(x, y, z);
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string);
        string++;
    }
}

// Function to draw the room (4 walls, floor, ceiling)
void drawRoom() {
    // Floor (Gray)
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex3f(-5.0, 0.0, 5.0);
        glVertex3f(5.0, 0.0, 5.0);
        glVertex3f(5.0, 0.0, -5.0);
        glVertex3f(-5.0, 0.0, -5.0);
    glEnd();

    // Ceiling (White)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(-5.0, 5.0, 5.0);
        glVertex3f(5.0, 5.0, 5.0);
        glVertex3f(5.0, 5.0, -5.0);
        glVertex3f(-5.0, 5.0, -5.0);
    glEnd();

    // Left Wall (Red)
    glColor3f(0.9, 0.2, 0.2);
    glBegin(GL_QUADS);
        glVertex3f(-5.0, 0.0, 5.0);
        glVertex3f(-5.0, 5.0, 5.0);
        glVertex3f(-5.0, 5.0, -5.0);
        glVertex3f(-5.0, 0.0, -5.0);
    glEnd();

    // Right Wall (Red)
    glColor3f(0.9, 0.2, 0.2);
    glBegin(GL_QUADS);
        glVertex3f(5.0, 0.0, 5.0);
        glVertex3f(5.0, 5.0, 5.0);
        glVertex3f(5.0, 5.0, -5.0);
        glVertex3f(5.0, 0.0, -5.0);
    glEnd();

    // Back Wall (Yellow)
    glColor3f(0.9, 0.9, 0.2);
    glBegin(GL_QUADS);
        glVertex3f(-5.0, 0.0, -5.0);
        glVertex3f(5.0, 0.0, -5.0);
        glVertex3f(5.0, 5.0, -5.0);
        glVertex3f(-5.0, 5.0, -5.0);
    glEnd();

    // Draw Smartboards on the back wall
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -2.0; i <= 2.0; i += 2.0) {
        glBegin(GL_QUADS);
            glVertex3f(i - 1.0, 2.5, -4.9);
            glVertex3f(i + 1.0, 2.5, -4.9);
            glVertex3f(i + 1.0, 4.5, -4.9);
            glVertex3f(i - 1.0, 4.5, -4.9);
        glEnd();
    }

    // Draw text on the smartboard
    const char* text = "GRAPHICS 301 AKA GROUP6";
    float textWidth = strlen(text) * 0.2f;
    float centerX = -textWidth / 2.0f;
    glColor3f(0.0, 0.0, 0.0);
    drawString(centerX, 3.5, -4.8, text);
}

// Global variable to track the state of the monitor

bool monitorOn = true;


// Function to draw a monitor on the table
void drawMonitor(float x, float z) {
    // Monitor base
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
        glVertex3f(x - 0.3, 1.6, z - 0.5);
        glVertex3f(x + 0.3, 1.6, z - 0.5);
        glVertex3f(x + 0.3, 1.7, z - 0.5);
        glVertex3f(x - 0.3, 1.7, z - 0.5);
    glEnd();

    // Monitor screen
    if (monitorOn) {
        glColor3f(0.5, 0.7, 1.0); // Light blue color
    } else {
        glColor3f(0.0, 0.0, 0.0); // Black color
    }
    glBegin(GL_QUADS);
        glVertex3f(x - 0.53, 1.78, z - 0.5);
        glVertex3f(x + 0.53, 1.78, z - 0.5);
        glVertex3f(x + 0.53, 2.42, z - 0.5);
        glVertex3f(x - 0.53, 2.42, z - 0.5);

    glEnd();

    // Monitor screen border
    glLineWidth(4.0);
    glColor3f(0.0, 0.0, 0.0); // Black color
    glBegin(GL_LINES);
        glVertex3f(x - 0.55, 1.75, z - 0.5);
        glVertex3f(x + 0.55, 1.75, z - 0.5);
        glVertex3f(x + 0.55, 1.75, z - 0.5);
        glVertex3f(x + 0.55, 2.45, z - 0.5);
        glVertex3f(x + 0.55, 2.45, z - 0.5);
        glVertex3f(x - 0.55, 2.45, z - 0.5);
        glVertex3f(x - 0.55, 2.45, z - 0.5);
        glVertex3f(x - 0.55, 1.75, z - 0.5);
    glEnd();


}

//student
void drawStudent() {
    glColor3f(0.0f, 0.5f, 1.0f);
    glutSolidSphere(0.5f, 20, 20); // Head
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(0.6f, 1.0f, 0.6f);
    glutSolidCube(1.0f); // Body
    glPopMatrix();
}

void drawRobotArm(float angle) {

    // Upper arm
    glColor3f(0.8f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f); // Hinge movement
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(0.2f, 1.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Lower arm
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glRotatef(-angle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(0.2f, 1.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

}
void drawRobotLeg(float angle) {
    // Upper leg
    glColor3f(0.0f, 0.0f, 0.8f);
    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f); // Hinge movement
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(0.3f, 1.0f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Lower leg
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glRotatef(-angle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(0.3f, 1.0f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawRobot(float armAngle, float legAngle) {
    // Robot body
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(1.0f);

    // Draw robot arms
    glPushMatrix();
    glTranslatef(0.6f, 0.5f, 0.0f);
    drawRobotArm(armAngle); // Right arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, 0.5f, 0.0f);
    drawRobotArm(armAngle); // Left arm
    glPopMatrix();

    // Draw robot legs
    glPushMatrix();
    glTranslatef(0.3f, -0.7f, 0.0f);
    drawRobotLeg(legAngle); // Right leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, -0.7f, 0.0f);
    drawRobotLeg(legAngle); // Left leg
    glPopMatrix();
}
void update(int value) {
    // Animate robot arm movement
    if (armIncreasing) {
        armAngle += 2.0f;
        if (armAngle > 45.0f) armIncreasing = false;
    } else {
        armAngle -= 2.0f;
        if (armAngle < -45.0f) armIncreasing = true;
    }

    // Animate robot leg movement
    if (legIncreasing) {
        legAngle += 2.0f;
        if (legAngle > 30.0f) legIncreasing = false;
    } else {
        legAngle -= 2.0f;
        if (legAngle < -30.0f) legIncreasing = true;
    }

    glutPostRedisplay(); // Request display update
    glutTimerFunc(16, update, 0); // Update every ~16ms (~60 FPS)

}
// Function to draw a simple table
void drawTable(float x, float z) {
    // Draw table top
    glColor3f(0.8, 0.4, 0.1);
    glBegin(GL_QUADS);
        glVertex3f(x - 1.5, 1.5, z - 2.0);
        glVertex3f(x + 1.5, 1.5, z - 2.0);
        glVertex3f(x + 1.5, 1.5, z + 0.0);
        glVertex3f(x - 1.5, 1.5, z + 0.0);
    glEnd();

    // Draw table legs
    glColor3f(0.5, 0.3, 0.1);
    for (float legX = -1.3; legX <= 1.3; legX += 2.6) {
        for (float legZ = -1.9; legZ <= -0.1; legZ += 1.8) {
            glPushMatrix();
            glTranslatef(x + legX, 0.75, z + legZ);
            glScalef(0.1, 1.5, 0.1);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }

    // Draw monitor on the table
    drawMonitor(x, z);
}

// Function to draw a simple chair
void drawChair(float x, float z) {
    // Draw chair seat
    glColor3f(0.6, 0.3, 0.1);
    glBegin(GL_QUADS);
        glVertex3f(x - 0.5, 0.75, z - 0.5);
        glVertex3f(x + 0.5, 0.75, z - 0.5);
        glVertex3f(x + 0.5, 0.75, z + 0.0);
        glVertex3f(x - 0.5, 0.75, z + 0.0);
    glEnd();

    // Draw chair backrest
    glBegin(GL_QUADS);
        glVertex3f(x - 0.5, 1.25, z);
        glVertex3f(x + 0.5, 1.25, z);
        glVertex3f(x + 0.5, 0.75, z);
        glVertex3f(x - 0.5, 0.75, z);
    glEnd();

    // Draw chair legs
    glColor3f(0.5, 0.3, 0.1);
    float leg_positions[4][2] = {
        {-0.4, -0.5},
        {0.4, -0.5},
        {-0.4, 0.0},
        {0.4, 0.0}
    };

    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef(x + leg_positions[i][0], 0.25, z + leg_positions[i][1]);
        glScalef(0.1, 1.0, 0.1);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}

// Function to draw a window on the right wall
void drawWindow() {
    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(4.9, 3.0 , 2.5);
        glVertex3f(4.9, 3.0, -2.5);
        glVertex3f(4.9, 4.5, -2.5);
        glVertex3f(4.9, 4.5, 2.5);
    glEnd();
}

// Global variable to track the ray offset
float rayOffset = 0.0f;

// Function to draw sunlight rays
// Function to draw realistic sunlight rays with thickness and transparency
void drawSunlight() {
    float rayLength = 12.0f;       // Length of each ray
    float baseRayThickness = 0.2f;  // Base thickness of rays
    int rayCount = 10;              // Number of rays to draw
    float raySpacing = 0.5f;        // Spacing between rays
    float rayOffset = 0.0f;         // Offset for ray positioning

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Generate sun rays
    for (int i = 0; i < rayCount; ++i) {
        // Angle for each ray
        float angleRad = (angle - 90.0f + i * 90.0f / rayCount) * M_PI / 180.0f;
        float rayY = -2.15 + -sin(angleRad) * rayLength; // Y-coordinate for ray end
        for (int j = 0; j < 4; ++j) {
            float rayThickness = baseRayThickness - (j * 0.04f); // Decrease thickness for inner rays
            glLineWidth(rayThickness);

            glBegin(GL_LINES);
                // Set color with varying alpha for realism
                float yellowIntensity = 0.5f; // Bright yellow
                float alpha = 0.6f - (j * 0.2f);
                glColor4f(yellowIntensity, yellowIntensity * 0.8f, 0.0, alpha); // Set the ray color
                glVertex3f(4, 4, 2);            // Start point of the ray
                glVertex3f(-10.0f + rayOffset, rayY, -5.0f); // End point of the ray
            glEnd();
        }

        // Increment the offset for the next ray
        rayOffset += raySpacing;
        if (rayOffset > 1.0f) {
            rayOffset -= 1.0f; // Reset offset to create a looping effect
        }
    }

    // Disable blending after drawing
    glDisable(GL_BLEND);
}



// Rotation angle for the ceiling fan
float fanAngle = 0.0f;

// Function to draw a ceiling fan
void drawFan(float x, float y, float z) {
    // Draw fan body (cylinder)
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(x, y, z);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.4, 0.4, 0.2, 32, 32);
    glPopMatrix();

    // Draw fan blades
    glColor3f(0.7, 0.7, 0.7);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(x, y - 0.45f, z);
        glRotatef(fanAngle + i * 90, 0.0, 1.0, 0.0); // Rotate around y-axis
        glBegin(GL_QUADS);
            glVertex3f(-1.5, 0.0, 0.0);
            glVertex3f(1.5, 0.0, 0.0);
            glVertex3f(1.5, 0.0, -0.4);
            glVertex3f(-1.5, 0.0, -0.4);
        glEnd();
        glPopMatrix();
    }
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera view
    gluLookAt(0.0, 3.0, 10.0, 0.0, 3.0, 0.0, 0.0, 1.0, 0.0);

    // Draw room elements
    drawRoom();
    drawFan(0.0, 5.0, 0.0);  // Draw fan at position
    drawWindow();
    drawSunlight();

    // Draw multiple tables, students, robots, and chairs
    float tablePositions[8][2] = {
        {-2.0, -2.0}, {2.0, -2.0}, {-2.0, 2.0}, {2.0, 2.0},
        {-4.0, -2.0}, {4.0, -2.0}, {-4.0, 2.0}, {4.0, 2.0}
    };

    for (int i = 0; i < 8; ++i) {
        // Draw tables at the positions
        drawTable(tablePositions[i][0], tablePositions[i][1]);

        // Optionally draw students and robots on some of the tables
        if (i < 5) {  // Only for the first 5 tables, as per the original logic
            glPushMatrix();
            glTranslatef(0.0f, 1.0f, 0.0f);  // Position students on the desks
            drawStudent();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0f, 2.0f, 0.0f);  // Position robots on the desks
            drawRobot(armAngle, legAngle);
            glPopMatrix();
        }

        // Draw chairs with the tables
        drawChair(tablePositions[i][0], tablePositions[i][1]);
    }

    glutSwapBuffers();
}

// Function to update the fan angle
void updateFanAngle(int value) {
    fanAngle += 1.0f;
    if (fanAngle > 360.0f) {
        fanAngle -= 360.0f;
    }

    // Increment the ray offset to create the illusion of movement
    rayOffset += 1.0f; // Reduce the increment to make the rays move slower
    if (rayOffset > 1.0f) {
        rayOffset -= 1.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateFanAngle, 0);//Continuous movement of the fan
}

// Function to toggle the monitor state
void toggleMonitor() {
    monitorOn = !monitorOn;
}

// Function to handle mouse clicks
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        toggleMonitor();
        glutPostRedisplay();
    }
}


// Function to handle window resizing
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Students Building a Robot");

    init();  // Initialize OpenGL settings
    glutDisplayFunc(display);  // Set the display callback function
    glutMouseFunc(mouseClick);  // Set the mouse callback function
    glutTimerFunc(16, update, 0);  // Set the update function to animate robot movement
    glutTimerFunc(16, updateFanAngle, 0);  // Set the update function to animate fan movement
    glutMainLoop();  // Enter the main loop

    return 0;
}

