inherit NPC;
void create()
{
        set_name("��ͷ", ({ "biaotou" }) );
        set("gender", "����" );
        set("age", 25);
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("per",2);
        set("chat_chance", 2);
        set("chat_msg",({
        "��ͷ�ȵ����������˵������ˡ���\n",
        "��ͷ�ȵ��������߿��ߣ���͵������\n",
    }) );

        set_temp("no_return",1);
        setup();
        carry_object("/clone/armor/bcloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
}
