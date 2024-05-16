using System;

namespace Spore
{
    public class Object
    {
        protected Object()
        {
            ID = 0;
        }

        internal Object(ulong id)
        {
            ID = id;
        }

        //public readonly ulong ID;
        public ulong ID;

        public Vector3 Position
        {
            get
            {
                InternalCalls.TransformComponent_GetPosition(ID, out Vector3 result);
                return result;
            }
            set
            {
                InternalCalls.TransformComponent_SetPosition(ID, ref value);
            }
        }

        public bool HasComponent<T>() where T : Component, new()
        {
            Type componentType = typeof(T);
            Console.WriteLine(componentType.FullName);
            return InternalCalls.Object_HasComponent(ID, "Transform");
        }

        public T GetComponent<T>() where T : Component, new()
        {
            if (!HasComponent<T>())
            {
                Console.WriteLine("No Component");
                return null;
            }
            T component = new T() { Object = this };
            return component;
        }

        public Object FindObjectByName(string name)
        {
            ulong objectID = InternalCalls.Object_FindObjectByName(name);
            if(objectID == 0)
                return null;

            return new Object(objectID);
        }

        public T As<T>() where T : Object, new()
        {
            object instance = InternalCalls.GetScriptInstance(ID);
            return instance as T;
        }
    }
}
