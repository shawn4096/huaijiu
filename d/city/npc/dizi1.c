// dizi1.c

inherit NPC;

void create()
{
        set_name("С��ؤ",({ "xiao qigai", "qigai", "beggar" }) );
        set("gender", "����" );
        set("age", 10);
        set("long", "����һ������ؤ���С���ӣ����ϻ����������Ц�ݡ�\n");
	

        set("shen", -100);
        set("shen_type", -1);
        set("str", 15);
        set("dex", 18);
        set("con", 15);
        set("int", 17);
        set("combat_exp", 200);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 10);
        set("attitude", "peaceful");
        setup();
        
}

