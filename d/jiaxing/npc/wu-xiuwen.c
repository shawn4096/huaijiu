// wu-santong.c ����ͨ
// by shang 97/6

inherit NPC;

void create()
{
        set_name("������", ({ "wu xiuwen", "wu" }) );
	set("gender", "����" );
        set("age", 11);
	set("long",
"����ͨ��С���ӡ \n" "��ѧ���ҵĶ��ӣ�ȴȡ�˸�˹�����֡�\n");
	set("attitude", "friendly");
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 22);
        set("shen_type", 1);

        set_skill("unarmed", 35);
        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set("jiali", 10);

        set("combat_exp", 4000);

        set("max_qi", 250);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("max_jingli", 100);

        set("inquiry", ([
            "������" : "�����",
            "�����" : "�����Ҹ�硣",
            "����ͨ" : "����ô�����ڶ�����ǰ�����ӵ�����? ",
            "here" : "������·, Ҳ��֪�������",
       ]) );
	setup();
        carry_object("/d/city/obj/cloth")->wear();
}
