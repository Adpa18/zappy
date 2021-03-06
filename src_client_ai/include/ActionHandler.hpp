//
// Created by gaspar_q on 3/18/16.
//

#ifndef C_ACTIONCOMPONENT_HPP
#define C_ACTIONCOMPONENT_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>

class NoActionException : public std::runtime_error
{
public:
    NoActionException() :
            std::runtime_error("ActionHandler: No such action selected")
    {
    }
    virtual ~NoActionException()
    {

    }
    using std::runtime_error::what;
};

/**
 * \brief Class used to associate an element to a specific type of actions
 *
 * \param elementType The type of the linked elem used for method calls
 * \param actionType The type of the actions that will be used with the element
 */
template<typename elementType, typename actionRet = void>
class ActionHandler
{
private:
    typedef actionRet (elementType::*methodType)();

    typedef typename std::vector<methodType> actionVector;
    typedef typename actionVector::iterator actionIterator;

public:
    /**
     * \brief Constructor of ActionHandler
     *
     * \param element The element that will be used to handle callbacks
     */
    ActionHandler(elementType &elementRef) :
            element(elementRef),
            actions(),
            currAction(actions.size()),
            isCurrActionSet(false)
    {
    }

    /**
     * \brief Constructor of ActionHandler with an handler
     *
     * \param element The element that will be used to handle callbacks
     * \param newAction The first handler of the ActionHandler
     */
    template<typename handlerType>
    ActionHandler(elementType &elementRef, handlerType newAction) :
            ActionHandler(elementRef)
    {
        *this << newAction;
    }

    /**
     * \brief Destructor of ActionHandler
     */
    ~ActionHandler()
    {
    }

    /**
     * \brief Copy constructor for coplien
     *
     * \param component The component to copy
     */
    ActionHandler(ActionHandler<elementType, actionRet> const &component) :
            element(component.element)
    {
        *this = component;
    }

    /**
     * \brief Copy operator for coplien
     *
     * \param ref The reference to copy
     * \return The reference to this
     */
    ActionHandler<elementType, actionRet> &operator=(ActionHandler<elementType, actionRet> const &ref)
    {
        actions = ref.actions;
        isCurrActionSet = ref.isCurrActionSet;
        currAction = ref.currAction;
        return *this;
    }

public:

    /**
     * \brief The operator to call a method
     *
     * \return The pointer to the element used to call methods
     */
    elementType *operator->()
    {
        return &element;
    }

    /**
     * \brief The operator to access to element
     *
     * \return The element used for method calls
     */
    elementType &operator*()
    {
        return element;
    }

    /**
     * \brief Feed operator for adding actions to handler
     *
     * \param newAction The new action to feed to the handler
     */
    template<typename handlerType>
    void            operator<<(handlerType newAction)
    {
        actions.push_back((methodType) newAction);
        currAction = 0;
        isCurrActionSet = true;
    }

    /**
     * \brief Multi access operator for accessing the method of the handler we want. Throws std::out_of_range
     *
     * \param index The index of the method you want to get
     * \return The method you ask for
     */
    ActionHandler<elementType, actionRet> &operator[](size_t index) throw(std::out_of_range)
    {
        if (index >= actions.size())
            throw std::out_of_range("ActionHandler: No such function at this index");
        currAction = index;
        return *this;
    }

    /**
     * \brief Operator parenthesis for call of selected method
     */
    template<typename ... Types>
    actionRet       operator()(Types ... args) throw(NoActionException)
    {
        if (currAction == actions.size())
        {
            std::cerr << "\e[31m" + std::to_string(currAction) + ") for size " + std::to_string(actions.size()) + "\e[0m" << std::endl;
            throw NoActionException();
        }
        typedef actionRet (elementType::*realMethod)(Types...);

        realMethod method = (realMethod) actions[currAction];

        return (element.*method)(args...);
    }

    /**
     * \brief Get the number of handled methods
     */
    size_t getHandleNumber() const
    {
        return actions.size();
    }

    /**
     * \brief Convert a call to a method into a std::function
     * \return Standard function corresponding to the call
     */
    template <typename ... Types>
    std::function<actionRet(Types...)>   toFunction()
    {
        typedef actionRet (elementType::*realMethod)(Types...);

        return MethodToFunction<Types...>(element, (realMethod)actions[currAction]);
    }

    /**
     * \brief Convert a call to a method into a wraped std::function
     * \param args All arguments to push
     * \return Stardard function wrapped corresponding to the call of the method
     */
    template <typename ... Types>
    std::function<actionRet()>  toWrapedFunction(Types&& ... args)
    {
        return std::bind(toFunction<Types...>(), std::forward<Types>(args)...);
    }

    /**
     * \brief Convert a method call to a function
     * \param elem A reference on the object to which call the method
     * \param method A pointer on the method to call
     * \return A standard function corresponding to the method to call
     */
    template <typename methType, typename ... Types>
    static std::function<actionRet(Types...)>   MethodToFunction(elementType &elem, methType method)
    {
        return [&elem, method] (Types&& ... params) {
                return ((elem.*method)(params...));
            };
    }

    /**
     * \brief Convert a call to a method into a wraped std::function
     * \param elem A reference on the object to which call the method
     * \param method The method to call
     * \param args All the arguments to wrap in the function
     * \return A Standard function corresponding to the call of the method
     */
    template <typename methType, typename ... Types>
    static std::function<actionRet()>   MethodToWrapedFunction(elementType &elem, methType method, Types&& ... args)
    {
        return std::bind(MethodToFunction<Types...>(elem, method), std::forward<Types>(args)...);
    }

private:
    elementType &element;
    actionVector actions;
    size_t currAction;
    bool isCurrActionSet;
};

#endif //C_ACTIONCOMPONENT_HPP
