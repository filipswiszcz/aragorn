#include <string>
#include <vector>

#ifndef CONTEXT_H
#define CONTEXT_H

namespace core {

    class ContextInit {

        public:

            

        protected:

            void init_glew();

            void init_glfw();

        private:

            std::vector<std::string> extensions;
            uint32_t counter;

            bool glew_running, glfw_running;

            void init_glew();

            void init_glfw();

    };

} // namespace core

#endif