inline ze::ConsoleWriter& ze::ConsoleWriter::Get()
{
   static ConsoleWriter writer;
   return writer;
}

