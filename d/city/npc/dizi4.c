// dizi4.c

inherit NPC;

void create()
{
        set_name("����ؤ", ({ "lao qigai", "qigai", "beggar" }) );
        set("long","����һ��������ؤ�����������ƣ����޲Բԣ���Ȼ���������ٷ�˪��\n");
	
        set("gender", "����");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 20);
        set("int", 16);
        set("con", 20);
        set("dex", 20);

        set("max_qi", 400);
        set("max_jing", 400);
        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 10);
        set("combat_exp", 4000);

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("parry", 40);


        setup();
 
}

