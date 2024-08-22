# Описание
Проект основан на примере Qt websockets/echoserver.  
Представляет собой реализацию WebSocket сервера, который принимает и обрабатывает сообщения по протоколу JSON RPC 2.0.

# Зависимости
Для обработки протоколов используется библиотека [jsonrpcx/json-rpc-cxx](https://github.com/jsonrpcx/json-rpc-cxx)  
Сама библиотека имеет зависимость [nlohmann/json](https://github.com/nlohmann/json)

Для сборки необходимо поместить в папку проекта папки с заголовочными файлами вышеприведенных библиотек, пример:  

    /jsonrpccxx  
        /common.hpp  
        /...  
    /nlohmann  
        /json.hpp  
        /...  


# Основные классы
SocketDispatcher – Обработчик соединений WebSocket. Реализация из примера с заменой разбора строк на разбор протокола JSON RPC.  
ProcedureServer – Непосредственный обработчик RPC. Отвечает за CRUD объектов классов Account и Person.  
В QList класса ProcedureServer хранятся указатели на объекты класса Person  

Person – Класс с полями и соответствующими им propery name и age.  
Имеет дочерние объекты класса Account (QObject child)  
Имеет сигнал nameChanged, который вызывает обновление проперти link всех детей класса Account  
Person name NOTIFY -> Account setLink  
Person setName -> Account setLink  

Account – Класс с полями и соответствующими им propery link и website.  
Если явно не удаляется путем вызова соответствующего метода RPC, время жизни как у родительского Person.

# Список команд RPC
    createPerson { name, age }  
    readPerson { name }  
    updatePerson { old_name, new_name, new_age }  
    deletePerson { name }  
    
    listPerson  
    
    createAccount { person_name, website }  
    readAccount { person_name, website }  
    deleteAccount { person_name, website }  
    
    listAccount { person_name }  

# Использование
Набор тестовых запросов представлен в файле test.json  
В качестве клиентской стороны для проверки - echoclient.html