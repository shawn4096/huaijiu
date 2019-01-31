// tuoboseng.c
// Date: YZC 96/01/19

inherit NPC;

void create()
{
        set_name("�в�ɮ", ({"tuobo seng","seng"}));
        set("title", "���ֵ���");
        set("long",
                "����һλδͨ���ʵ�������У����Ϲ��ź������΢Ц��\n"
        );

        set("gender", "����");
        set("attitude", "heroism");
        set("class", "bonze");

        set("age", 20);
        set("shen_type", 1);
        set("str", 15);
        set("int", 30);
        set("con", 30);
        set("dex", 18);
        set("max_qi", 280);
        set("max_jing", 300);
        set("neili", 380);
        set("max_neili", 380);
        set("jiali", 27);
        set("combat_exp", 10000);
        set("shen_type", 1);
        set("chat_chance", 30);

        set("chat_msg", ({
                "�в�ɮ˵��: ����λʩ�����������Ӹ�ƶɮ���������£��츣������\n",
                (: random_move :)
        }) );

        set_skill("force", 41);
        set_skill("unarmed", 41);
        set_skill("dodge", 41);
        set_skill("parry", 41);
        set_skill("shaolin-shenfa", 42);
        set_skill("jingang-quan", 41);
        set_skill("yijin-jing", 41);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("unarmed", "jingang-quan");
        map_skill("parry", "jingang-quan");

        create_family("������", 40, "����");
        setup();
        carry_object("/d/city/obj/cloth")->wear();

        setup();

}

int accept_object
(object me, object ob)
{
        object ling;
//add by look@SJ because ���˽�ر��
//add by caiji@SJ because �����³��ҵ��ӽ��������֡�
                if( ob->query("money_id") && ob->value() >= 10000 && ((me->query("class") != "bonze"&&(me->query("family/family_name") != "������"))
                 || me->query("gender")== "Ů��")) 
        {
                command("smile");
            command("say �����ӷ𣬶�л��λ" + RANK_D->query_respect(me) + " ��");
            command("say " + RANK_D->query_respect(me) + 
            "������ƺ�ʩ�����������գ����·�������һ������Ӣ�ۣ���֪��Ը����������һ�Σ�");
            ling=new("/d/shaolin/obj/tie-ling");
            ling->move(me);
            message_vision("�в�ɮ��$Nһ���������ơ�\n", me);
            command("say ������ʱһ�գ���ʱʧЧ��������ʱǰ���£�������в��㣬�м��мǣ�"); 
        }
                else return notify_fail("�в�ɮ˵����" + RANK_D->query_respect(me) + "��ƶɮ��Щ��������֪�Ǻ����⣿\n");
        return 1;
}
