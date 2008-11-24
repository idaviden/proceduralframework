#include "stdafx.h"
#include "Framework.h"
#include "FileHeightmap.h"
#include "Vector3.h"
#include "GL/glew.h"
#include "GL/glfw.h"



Framework::Framework(int p_width, int p_height)
{
	m_width = p_width;
	m_height = p_height;

	camera = new Camera(Vector3<float>(10, 500, 10), Vector3<float>(0,0,0));


	

}


void Framework::Init(){
	
	int ok;

	glfwInit();

	ok = glfwOpenWindow(
							m_width, m_height,          // Width and height of window
							8, 8, 8,           // Number of red, green, and blue bits for color buffer
							8,                 // Number of bits for alpha buffer
							24,                // Number of bits for depth buffer (Z-buffer)
							0,                 // Number of bits for stencil buffer
							GLFW_WINDOW        // We want a desktop window (could be GLFW_FULLSCREEN)
						);

    // If we could not open a window, exit now
    if( !ok )
    {
        glfwTerminate();
    }

	int err=glewInit();
	if(err!=GLEW_OK)
	{
		glfwTerminate();
	}

    // Set window title
    glfwSetWindowTitle( "POC I - Fabio Miranda" );

	// Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );
	//glfwEnable( GLFW_KEY_REPEAT );

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	glEnable(GL_TEXTURE_2D);

	m_isRunning = true;


	






	
	

	


}

int Framework::Start(){
	
	Init();


	while(m_isRunning){
		DoUpdate();
		DoRender();
		glfwSwapBuffers();

		m_isRunning = (!glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED ));


	}

	glfwTerminate();
	return 0;

}

void Framework::GLConfig(){
	double t;              // Time (in seconds)

    // Get current time
    t = glfwGetTime();

    glfwGetWindowSize( &m_width, &m_height );
    glViewport( 0, 0, m_width, m_height );

    // Clear color and depht buffers
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // Set up projection matrix
    glMatrixMode( GL_PROJECTION );    // Select projection matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluPerspective(                   // Set perspective view
        90.0,                         // Field of view = 65 degrees
        (double)m_width/(double)m_height, // Window aspect (assumes square pixels)
        1.0,                          // Near Z clipping plane
        10000.0                         // Far Z clippling plane
    );

    // Set up modelview matrix
	/*
    glMatrixMode( GL_MODELVIEW );     // Select modelview matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluLookAt(                        // Set camera position and orientation
        0.0, 0.0, 10.0,               // Camera position (x,y,z)
        0.0, 0.0, 0.0,                // View point (x,y,z)
        0.0, 1.0, 0.0                 // Up-vector (x,y,z)
    );
	*/


	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glRotatef(camera->m_rotation.GetX(),1.0,0.0,0.0); //rotate our camera on teh x-axis (left and right)
	glRotatef(camera->m_rotation.GetY(),0.0,1.0,0.0); //rotate our camera on the y-axis (up and down)
	glTranslated(-camera->m_pos.GetX(),-camera->m_pos.GetY(),-camera->m_pos.GetZ()); //translate the screen to the position of our camera



	
}



void Framework::DoUpdate(){
	camera->Update();

	if(glfwGetKey( 'Q' )){
		m_wireFrame = ~m_wireFrame;

	}

}

void Framework::DoRender(){

	GLConfig();
	
	//Light
	Framework::InitLight();

	
	m_currentNode->Render(m_wireFrame);


	//See if the camera is on another node. If so, we have to generate its neighbours
	if(m_currentNode->IsWithin(camera->m_pos) == false){

		m_currentNode = m_currentNode->FindCurrentStandingNode(camera->m_pos);
	}

	/*
	for (m_iterator = m_sceneGraph.begin(); m_iterator != m_sceneGraph.end(); m_iterator++ )
	{
		Node& node = **m_iterator;

		//cout << &node;
		//cout << "\n";

		node.Render();

		
		//See if the camera is on the node
		if(node.IsWithin(camera->m_pos)){

			//See if the node is different from the last one (so we have to generate more patchs)
			if(m_currentNode->m_position.equals(node.m_position) == false){
				//cout << "caiu";

				node.GenerateNeighbours(m_currentNode);


				m_currentNode = &node;

			}

			//node.GenerateNeighbours();
		}
	}
	*/

	
}

void Framework::InitLight(){
	//Light
	
	glEnable(GL_LIGHT0);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);


	GLfloat light_ambient[] =
	{0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] =
	{1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] =
	{1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[] =
	{0.0, 10.0, -25.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	


}