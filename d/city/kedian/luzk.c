#include <skill.h> 
#include <ansi.h>

inherit NPC;
int do_learn(string arg);

void create()
{
        set_name("¹�ȿ�", ({ "lu zhangke", "lu", "zhangke" }) );
        set("nickname", HBBLU"��ڤ����"NOR);
        set("long", "��������ڤ�����е�¹�ȿ͡�\n");
        set("gender", "����" );
        set("age", 55);
        set("apprentice", 1);
        set("attitude", "peaceful");
        set("str",25);
        set("int",25);
        set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);
        
        set("max_qi", 5000);
        set("max_jing", 3500);
        set("neili", 8000);
        set("jiali", 100);
        set("combat_exp", 4200000);
        set("eff_jingli",6000);

        set_skill("force", 280);
        set_skill("xiantian-gong", 280);
        set_skill("dodge", 290);
        set_skill("tiyunzong", 290);
        set_skill("strike", 300);
        set_skill("xuanming-shenzhang", 300);
        set_skill("parry", 280);
        set_skill("literate", 200);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiyunzong");
        map_skill("strike", "xuanming-shenzhang");
        map_skill("parry", "xuanming-shenzhang");
        prepare_skill("strike", "xuanming-shenzhang");

        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
}

void init()
{
        add_action("do_learn","learn");
        add_action("do_learn","xue");
        ::init();
}

int do_learn(string arg)
{
        object me=this_player();
        string skill, teacher, skill_name;
        object ob;
        int master_skill, my_skill, gin_cost, rand;


        if (me->is_busy()) return 0;

        if (me->query("zhao_job",) < 500 ) return 0;
        if(!arg || (sscanf(arg, "%s %s", teacher, skill)!=2 ))  return 0;


        if( me->is_fighting() ) return 0;

        if( !(ob = present(teacher, environment(me))) || !ob->is_character()) {
                write("��Ҫ��˭��̣�\n");
                return 1;
        }

        if( !living(ob) ) {
                write("��....����Ȱ�" + ob->name() + "Ū����˵��\n");
                return 1;
        }

        if(!me->query("menggu") && !me->query("xmsz"))
                return 0;

        if (skill != "xuanming-shenzhang") {
                write("���������±����ұ���ѧ�ˡ�\n");
                return 1;
        }

        my_skill = me->query_skill(skill, 1);
        master_skill = ob->query_skill(skill, 1);
        if( my_skill >= master_skill ) {
                write("��������Ѿ��ܸ��ˣ�\n");
                return 1;
        }

        if( !SKILL_D(skill)->valid_learn(me) ) {
                write("�����ڲ���ѧϰ��ڤ���ơ�\n");
                return 1;
        }

        gin_cost = 150 / (int)me->query("int");

        if( !my_skill ) {
                gin_cost *= 2;
                me->set_skill(skill,0);
        }

        rand = random(20);
        if (rand == 4)
                gin_cost *= 2;
        else if (rand == 15)
                gin_cost += 4;
        if( (int)me->query("potential") < 1 ) {
                write("���Ǳ���Ѿ����ӵ������ˣ�û�а취��ѧ�ˡ�\n");
                return 1;
        }

        write("����¹�ȿ�����йء���ڤ���ơ������⡣\n");

        if( (int)me->query("jing") > gin_cost ) {
                if( (string)SKILL_D(skill)->type()=="martial"
                &&      my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) {
                        write("Ҳ����ȱ��ʵս���飬������Ľ��������޷���ᡣ\n");
                } 
                        if(skill_name = SKILL_D(skill)->query_skill_name(my_skill))
                                write("����������ָ�����ԡ�" + skill_name + "����һ���ƺ���Щ�ĵá�\n");
                        else
                                write("����������ָ�����ƺ���Щ�ĵá�\n");
                        me->add("potential", -1);
                        me->improve_skill(skill, random(me->query_int()));
        } 
        else {
                gin_cost = me->query("jing");
                write("�����̫���ˣ����ʲôҲû��ѧ����\n");
        }
        me->receive_damage("jing", gin_cost );
        return 1;
}

