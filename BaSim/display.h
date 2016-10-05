

void plot( std::vector<float> x, std::vector<float> y, float c1, float c2, float c3)
{
    // This is sloppy and needs to be changed, we could make the graph not be draw again every time, rather keep previous drawings and add the new points, same for the axis, and we could add text
    
    glfwMakeContextCurrent(graphs);
    {
        glLineWidth(1.0f);
        glBegin(GL_LINE_STRIP);
        {
            // Axis
            glColor3f(1.0, 1.0, 1.0);
            glVertex2f(graph_xBound-1,1-graph_yBound);
            glVertex2f(graph_xBound-1,graph_yBound-1);
            glVertex2f(1-graph_xBound,graph_yBound-1);
            
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        {
            // The plot
            glColor3f(c1,c2,c3);
            for (int i=0;i<y.size();i++)
            {
                glVertex2f(x[i]/time_lim*(2-2*graph_xBound)+graph_xBound-1,y[i]/y_lim*(2-2*graph_yBound)+graph_yBound-1);
            }
            
        }
        glEnd();
        glfwSwapBuffers(graphs);
        glfwPollEvents();
    }
    glfwMakeContextCurrent(win);
    //time_vect.size();
}

void graphsRefresh()
{
    glfwMakeContextCurrent(graphs);
    {
        plot(time_vect,bound_vect,0.0,0.1,0.1);
        plot(region_vect,bound_vect,0.1,0.1,0.0);
    }
    glfwMakeContextCurrent(win);
}
