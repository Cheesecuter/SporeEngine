using System;

namespace Spore
{
    public class Player : Object
    {
        private TransformComponent m_transform;

        public float Speed;
        public float Time = 0.0f;

        public void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");

            m_transform = new TransformComponent();
            m_transform = GetComponent<TransformComponent>();
            if(m_transform != null)
            {
                m_transform.Position = new Vector3(1.0f, 2.0f, 3.0f);
                m_transform.Rotation = new Vector3(0.0f, 1.0f, 0.0f);

                Vector3 position = m_transform.Position;
                Console.WriteLine($"({position.X}, {position.Y}, {position.Z})");
                Vector3 rotation = m_transform.Rotation;
                Console.WriteLine($"({rotation.X}, {rotation.Y}, {rotation.Z})");
            }

        }
    }

    public class Program
    {
        public static int Main(string[] args)
        {
            Console.WriteLine("Hello Mono");

            Player player = new Player();
            player.OnCreate();

            return 0;
        }
    }
}
