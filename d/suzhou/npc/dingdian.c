 // by Xiaoyao

inherit NPC;
#include <ansi.h>
void destroying(object, object);
int ask_skills();

void create()
{
        set_name("����", ({ "ding dian", "ding" }));
        set("long", "����������ף�ͷ��������ֱ���������������ò�������ֱ��ͬ��ɽ�е�Ұ�ˡ�\n");
        set("gender", "����");
        set("age", 35);
        set("unique", 1);

        set_skill("cuff", 120);
        set_skill("dodge", 120);
        set_skill("parry", 130);
        set_skill("qingmang-jian", 120);
        set_skill("taizu-quan", 150);
        set_skill("shenzhao-jing", 120);
        map_skill("dodge","qingmang-jian");
        map_skill("force","shenzhao-jing");
        map_skill("parry", "qingmang-jian");
        map_skill("cuff","taizu-quan");
        prepare_skill("cuff","taizu-quan");
        set("max_neili",3000);
        set("neili",3000);
        set("max_qi",1680);
        set("qi",1680);
        set("eff_jingli",1800);
        set("jingli",1800);
        set("jiali",100);
        set("inquiry", ([
		"����" : "��Ҳ��֪�����ֵ����������Ҳ�������࣬��Ը�ް���",
		"name": "���������Ҿ��Ƕ��䣬����ʲô���飿",
		"here": "����������ݼ������ٺ١�",
		"���վ�" : (: ask_skills :),
		"����" : "����������ݡ�",
		"���Ǿ�" : "���������ʲô����......",
		"���ǽ���" : "���������ʲô����......",
		"����ɽ" : "÷�����������յ�������Ф���Ӱ�����ô�������Ľ������ࡣ",
		"�Դ�ƽ" : "÷�����������յ�������Ф���Ӱ�����ô�������Ľ������ࡣ",
		"�ݳ���" : "÷�����������յ�������Ф���Ӱ�����ô�������Ľ������ࡣ",
		"÷����" : "����ī��÷��������������ϧ����ԩ������",
		"����" : "����˪��������Ѿ�ߡ�",
		"����˼" : "������˪���ĵ��������ǲ���Ū�˰���",
		"��˪��" : "�����Ǻ��ָ���С�㣬Ҳ�������İ����ˡ�",
	])); 
        set("combat_exp", 600000);
        set("shen_type", 1);
        setup();
        carry_object("/clone/armor/cloth")->wear();

}

int accept_object(object me, object obj)
{
        object key;
        me = this_player();
        if ((string)obj->query("id")=="lu juhua") {
        message("vision",me->name()+"������һ���̾ջ���\n",environment(me),
            ({me}));
        key = unew("/clone/armor/wucanyi");
        if(!clonep(key)) return notify_fail (CYN"����˵�������Ѿ����˸�˪���ӻ��ˣ�����������ˡ�\n"NOR);  
        if(clonep(key) && key->violate_unique()){
           destruct(key);
           return notify_fail (CYN"����˵�������Ѿ����˸�˪���ӻ��ˣ�����������ˡ�\n"NOR);
           } 
        command("touch "+me->query("id"));
        command("say ��λ"+RANK_D->query_respect(me)+"��˪���������ӻ��İ�,�ˣ����ǿ��ǿ�����ԧ�졣");
        key->move(me);        
        message_vision("$n�ݸ�$Nһ���ڲ��¡�\n", me, this_object() );
        command("say ��λ"+RANK_D->query_respect(me)+"����̫��л����,�����������ȥ�ðɡ�");
        if(!me->query("szj") && !me->query_temp("szj")) me->set_temp("szj",1);
        remove_call_out("destroying");
        call_out("destroying", 1, this_object(), obj);
        return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

int ask_skills() 
{
	object me = this_player();
	int i;
        if(me->query("szj"))
        {
                 if(me->query("potential") > 4)
		 {
                        message_vision("$N��$n����й����վ��İ��\n", me, this_object());
			me->receive_damage("jing", 10);
			tell_object(me,HIY"�����˶����ָ�㣬�����վ��İ����ƺ���Щ�ĵá�\n"NOR);
			me->add("potential",-(random(3)+1));
			if(me->query("potential") < 0) me->set("potential",0);
			if(me->query_skill("shenzhao-jing") >= 220) me->improve_skill("shenzhao-jing", 25+me->query_int()*2);
			
			else
			{    me->improve_skill("shenzhao-jing", 25+random(me->query_int()));
			     me->improve_skill("force", random(me->query_int())/2);
			  }
                      }
                 else 
		{
			message_vision("$N��$n����й����վ��İ��\n", me, this_object());
			tell_object(me,HIY"�����˶����ָ�㣬���ǻ��ǲ�����⡣\n"NOR);
		}
		return 1;
	}

        if(!me->query_temp("szj") && !me->query("szj")) 
                {
                        command("say �������������վ�������ī��÷�����������������ҵ�һ���ڹ����ؾ���");
                        return 1;
                        }

        if(me->query_temp("szj") && !me->query("szj")) 
                {
                        if(me->query("szj_fail") >= 3)
                        {
                                command("say �Ѿ���δ��ڣ���λ"+RANK_D->query_respect(me) +"��ô����û������");
                                return 1;
                          }
                        if(me->query("szj_exp") && me->query("combat_exp")-me->query("szj_exp")<50000)
                        {
                                command("say ��"+RANK_D->query_respect(me) +"��ǰ�ľ�����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
                                return 1;
                          }
        me->set("szj_exp",me->query("combat_exp")); 
	i= random(15);
	if(i==1)
	   {
		   command("say ��������ī��÷�����������������ҵ�һ���ڹ����ؾ����Ҿʹ��ڸ�"+RANK_D->query_respect(me) +"�ɡ�");
		   command("say ������Ч��......");		   
		   command("hehe "+me->query("id"));
		   tell_object(me,HIY"�����˶����ָ�㣬�����վ��İ����ƺ���Щ�ĵá�\n\n"NOR);
		   me->improve_skill("shenzhao-jing", 5+random(me->query_int()));
		   me->improve_skill("force", random(me->query_int())/2);
		   me->set("szj",1);
		   log_file("quest/szj", sprintf("%s(%s) ʧ��%d��ѧ�����վ�������iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("szj_fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		   command("say ��������ī��÷�����������������ҵ�һ���ڹ����ؾ����Ҿʹ��ڸ�"+RANK_D->query_respect(me) +"�ɡ�");
		   command("say ��������ģ����������֮�ھͿ������վ��ڹ��ķ����ٺ١�");
		   command("ah "+me->query("id"));
		   tell_object(me,HIY"�����˶����ָ�㣬���Ƕ����վ��İ���ȫȻ����Ҫ�졣\n\n"NOR);
		   command("sigh "+me->query("id"));
		   me->add("szj_fail",1);
		   command("courage");   		   
		   log_file("quest/szj", sprintf("%s(%s) ѧϰ���վ�ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("szj_fail"),i,me->query("combat_exp")) );
	   }
	  } 
	 return 1;
}