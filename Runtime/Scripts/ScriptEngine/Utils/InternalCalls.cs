using System;
using System.Runtime.CompilerServices;

namespace Spore
{
    public static class InternalCalls
    {
        #region Object
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Object_HasComponent(ulong objectID, string componentType);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static ulong Object_FindObjectByName(string name);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static object GetScriptInstance(ulong objectID);
        #endregion

        #region TransformComponent
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_SetPosition(ulong objectID, ref Vector3 translation);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_GetPosition(ulong objectID, out Vector3 translation);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_SetRotation(ulong objectID, ref Vector3 translation);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_GetRotation(ulong objectID, out Vector3 translation);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_SetScale(ulong objectID, ref Vector3 translation);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_GetScale(ulong objectID, out Vector3 translation);
        #endregion
    }
}
