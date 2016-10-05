

void plot( std::vector<float> x, std::vector<float> y)
{
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
            glColor3f(0.0, 1.0, 1.0);
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
        plot(time_vect,bound_vect);
    }
    glfwMakeContextCurrent(win);
}
