inherit NPC;

void create()
{
        set_name("ִ������", ({ "dizi" }));
        set("long","����һ������ִ�����ϵ�ؤ�����, �������̡�\n");
        
        set("gender", "����");
        set("age", 33);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 24);
        set("int", 18);
        set("con", 22);
        set("dex", 24);

        set("max_qi", 400);
        set("max_jing", 400);
        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 20);
        set("combat_exp", 5000);

        set_skill("force", 35);
        set_skill("dodge", 35);
        set_skill("unarmed", 35);
        set_skill("parry", 35);


        setup();

        set("chat_chance", 5);
        set("chat_msg", ({
              "ִ�����ӽе��������û�ã�������ؤ���е�����ô�á���\n",
        }) );

}

