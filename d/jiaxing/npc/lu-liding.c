// wu-santong.c ����ͨ
// by shang 97/6

inherit NPC;

void create()
{
        set_name("½����", ({ "lu liding", "lu" }) );
	set("gender", "����" );
        set("age", 35);
	set("long",
"������½չԪ֮��½������\n" "һ���书�����ֳ�½չԪ���������Ե�����\n" "һ��ϯ���ĺ񣬴Ӳ������������ߡ�\n");
	set("attitude", "friendly");
        set("str", 22);
        set("dex", 24);
        set("con", 20);
        set("int", 20);
        set("shen_type", 1);

        set_skill("unarmed", 50);
        set_skill("force", 50);
        set_skill("dodge", 60);
        set_skill("blade", 65);
        set("jiali", 20);

        set("combat_exp", 30000);

        set("max_qi", 300);
        set("max_jing", 200);
        set("neili", 300);
        set("max_neili", 300);
        set("max_jingli", 200);

        set("inquiry", ([
            "�����" : "����ɩ�ӡ�",
            "½չԪ" : "���������ֳ���",
       ]) );
	setup();
        carry_object(__DIR__"obj/gangdao")->wield();
        carry_object("/d/city/obj/cloth")->wear();
}
