namespace Core {
    class CoreError : public std::exception {
        private:
            std::string message;

        public:
            CoreError(std::string const &message) : message(message) {}
            virtual ~CoreError() throw() {}
            virtual const char *what() const throw() {
                return this->message.c_str();
            }
    };
}
