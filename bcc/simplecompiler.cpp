#include "simplecompiler.h"
#include <QVariant>
#include <QStringList>
#include <iostream>
#include "project.h"
#include "script.h"
#include <vector>
#include "block.h"
#include "pin.h"

#include "metascript/metascript.h"

simpleCompiler::simpleCompiler()
{
}
void simpleCompiler::configure(QCoreApplication& a)
{
  outputPath = a.property("output").toString();

  a.property("outputIndexSize");
  a.property("outputDebugfile");
}
bool simpleCompiler::compile(const blocks::project* pro)
{
  QStringList scriptNames = pro->getScriptList();

  int numScripts = scriptNames.count();

  if (numScripts > 0xFF)
  {
    std::cerr << "simple compiler does not support more than 255 scripts" << std::endl;
    return false;//FATAL
  }

  unsigned char rawNumScript= numScripts;

  programData.writeBytes((char*)&rawNumScript, sizeof(rawNumScript) );

  QStringList::const_iterator constIterator;
  for (constIterator = scriptNames.constBegin(); constIterator != scriptNames.constEnd(); ++constIterator)
  {
    blocks::script* s = pro->getScript(*constIterator);
    compileScript(*s,programData, debugData);
  }

  programData << "BLOC";
  return true;
}
bool simpleCompiler::compileScript(const blocks::script &s, QDataStream &ps, QDataStream &ds)
{
  std::vector<blocks::itemID> callList;
  metaScript script;
  script.makeFromScript(s);

  return true;
}
