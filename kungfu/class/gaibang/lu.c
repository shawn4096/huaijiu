inherit NPC;
inherit F_MASTER;

#include "gb_job.c"

string ask_job()
{
        object me = this_player();
        int exp = me->query("combat_exp");
        
/*      if(!(fam = me->query("family")) || fam["family_name"] != "ؤ��")
            return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��";

        if( me->query("shen") < 0 )
                return "�ҿ����ͷ��Ŀ����������ˣ�����ܷ��İѾ��������и����㡣\n";
*/
        if( exp < 3000 )
                return RANK_D->query_respect(me) + "���д��ģ��κ��书��Ϊ̫�\n";
                
        if( me->query_condition("job_busy") )
                return "����������û��ʲô������Ȼ������ɡ�\n";
                
        if( me->query("menggu") )
                return "�ߣ����⺺�飬����Ҫ����\n";

        if( exp < 80000 ){
                return gb_job1();
        }
        else if( exp < 500000 ){
                return gb_job2();
        }
        else if(exp < 1000000 ){
                return gb_job3();
        }
        else {
                return gb_job4();
        }
        return "������û��ʲô���Ը������������ˡ�\n";
}

int ask_num()
{
        object me=this_player();
    
        command( "say " 
        + RANK_D->query_respect(me) + "�Ѿ�Ϊ��������"
        + CHINESE_D->chinese_number( me->query("gb_job2") ) 
        + "�ι��ס�" );
        command("addoil " + me->query("id"));
        return 1;
}

string ask_me()
{
        object me = this_player();
        mapping fam;

        if (!(fam = me->query("family")) || fam["family_name"] != "ؤ��")
        {
                command("laugh " + me->query("id"));
                return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��";
        }
        if (random(4)) {
                command("hehe");
                return "�Ҳ�֪����";
        }
        if (query("count"))
        {
                new(__DIR__"obj/stick-book")->move(me); 
                add("count", -1);
                command(":(");
                message_vision("$N��$nһ��ֽƬ��\n", this_object(), me);
                return "�ðɣ��Ȿͼ������ȥ�о��������������ҡ�";
        }
        command("sigh " + me->query("id"));
        return "��������һ����ͼ���Ѿ����������ˡ�";
}

int qingjiao(string arg)
{
        object me = this_player();
        int lvl = me->query_skill("stick", 1);

        if (!living(me)) return 0;
        if (arg != "stick" || !present("stick book", me)) return notify_fail("��Ҫ���ʲô��\n");
        if (!living(this_object())) return notify_fail("���Ȱ���Ū����˵�ɣ�\n");
        if (lvl < 30) return notify_fail("��Ļ���������Ϊ��������³�нŵĽ����ƶ��Ƕ���\n");
        if (lvl < 101)
        {
                write("�����Ű���ͼ����³�н���̡�\n");
                me->receive_damage("jing", 30);
                write("��ġ����������������ˡ�\n");
                me->improve_skill("stick", me->query("int"));
                return 1;
        }
        command("blush " + me->query("id"));
        return notify_fail("");
}

void init()
{
        object me = this_player();
        int exp,pot,shen;
        
	::init();
        if( me->query_temp("gb_job2")
         && me->query_temp("gb_job2_finish")>=5 ){
                me->delete_temp("gb_job2");
                me->delete_temp("gb_job2_finish");
                exp = 400 + random(100);
                pot = exp/5+random(exp/6);
                shen = 600 + random(300);
                command("thumb "+me->query("id") );
                me->add("gb_job2",1);
                write( sprintf(HIW "�ã���������ˣ���õ���" 
                 + CHINESE_D->chinese_number( exp ) 
                 + "��ʵս���飬" 
                 + CHINESE_D->chinese_number( pot )
                 + "��Ǳ�ܺ�"
                 + CHINESE_D->chinese_number( shen ) 
                 + "������\n" NOR));

            log_file( "job/gbjob2", sprintf("%s %s(%s) ��ؤ����ղ��ϳ������񣬵õ�%d�㾭�顣\n",
            ctime(time())[4..19], me->query("name"), me->query("id"), exp ) );

            me->add( "combat_exp", exp );
            me->add( "potential", pot );
            if( me->query("potential") > me->query("max_pot") )
                me->set("potential", me->query("max_pot") );
            me->add( "shen", shen );
            me->apply_condition("job_busy",6);
        }    
        add_action("qingjiao", "qingjiao");
}

void create()
{
        set_name("³�н�", ({"lu youjiao", "lu", "youjiao"}));
        set("title", "ؤ��Ŵ�����");
        set("nickname", "�ư���ͷ");
        set("gender", "����");
        set("age", 45);
        set("long", 
                "³�н���Ȼ�书�㲻�ö�����֣������ڽ�����ȴ����������\n"
                "��Ϊ����ؤ�����������壬���¹������䣬��ú��߹������ء�\n");
        set("attitude", "peaceful");
        set("attitude", "peaceful"); 
        set("str", 25);
        set("int", 12);
        set("con", 25);
        set("dex", 20);
        set("unique", 1);
        set("no_bark",1);
        set("env/wimpy", 80);
        set("no_get","³�нŶ�����˵̫���ˡ�\n");

        set("qi", 900);
        set("max_qi", 900);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 100);
        
        set("combat_exp", 100000);
        set("score", 20000);
        
        set_skill("force", 90); // �����ڹ�
        set_skill("huntian-qigong", 90); // ��������
        set_skill("strike", 95); // ����ȭ��
        set_skill("xianglong-zhang", 90); // ����ʮ����
        set_skill("dodge", 90); // ��������
        set_skill("xiaoyaoyou", 90); // ��ң��
        set_skill("parry", 90); // �����м�
        set_skill("parry", 90); // �����м� 
        set_skill("stick", 85); // ��������
        set_skill("begging", 60);
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("strike", "xianglong-zhang");
        
        create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "����ͼ��" : (:ask_me:),
                "��Ч����" : (:ask_job:),
                "����": (: ask_num :),
                "���߹�": "�����ں�Ժ����������,ûʲô�²�Ҫ���š�\n",
        ]));
        set("count",1);

        setup();
}
